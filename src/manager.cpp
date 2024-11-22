#include <iostream>
#include <fstream>
#include <vector>
#include <manager.h>

/*----------------------------------------------------------------------------*/
static int park_num = 0;
int g_id;
std::mutex Manager::mtx_;
std::mutex Manager::report_cond_mtx_;
std::condition_variable Manager::report_cond_;

void report(int* id);
void check(int id);

SystemManager::SystemManager(int age, std::string &name, std::string& address, 
    std::string& wordID, int tel, int mode, std::string& worktime): 
Manager(age, name, address, wordID, tel, mode, worktime)
{
    is_stop = false;
    doing_ = std::thread(&SystemManager::check, this, g_id);
}

SystemManager::SystemManager(const SystemManager& manager)
{
    ;
}

SystemManager::~SystemManager(){
    is_stop = true;
    if (doing_.joinable())
    {
        doing_.join();
    }
}

void SystemManager::operator +(std::string& plate)
{
    std::ofstream file;
    file.open("../data/car.txt");
    if (file.is_open()) {
        file << "plate:" << plate << std::endl;
        file.close();
    } else {
        std::cout << "system error" <<std::endl;
    }
    return; 
}

void delete_car(std::string& plate)
{
    std::fstream file;
    file.open("../data/car.txt");
    if (file.is_open()) {
        std::string _plate;
        std::vector<std::string> lines;
        while (std::getline(file, _plate))
        {
            if (_plate.find(plate) != std::string::npos )
            {
                lines.push_back(_plate);
            }
        }
        for(const auto line : lines)
        {
            file << line << std::endl;
        }
        file.close();
    } else {
        std::cout << "system error" <<std::endl;
    }
    return; 
}

void SystemManager::operator -(std::string& plate)
{
    return delete_car(plate); 
}

void SystemManager::check(int id)
{
    auto now = std::chrono::system_clock::now();
    while(is_stop == false) {
        std::unique_lock<std::mutex> lock(report_cond_mtx_);
        report_cond_.wait_for(lock, std::chrono::seconds(2));
        handlingExceptions(id);
    } 
    return; 
}

void SystemManager::handlingExceptions(int orderID)
{
    std::fstream file;
    file.open("../data/order.txt");
    if (file.is_open()) {
        std::string  the_order;
        std::vector<std::string> lines;
        while (std::getline(file, the_order)){
            std::string str_orderID = std::to_string(orderID);
            if (the_order.find(str_orderID) != std::string::npos)
            {
                lines.push_back(str_orderID);
            }
        }
        for(const auto line : lines) {
            file << line << std::endl;
        }
        file.close();
    } else {
        std::cout << "system error" <<std::endl;
    }
    return; 
}

SystemGuard::SystemGuard(int age, std::string &name, std::string& address, 
    std::string& wordID, int tel, int mode, std::string& worktime): 
Manager(age, name, address, wordID, tel, mode, worktime)
{
    is_stop = false;
    doing_ = std::thread(&SystemGuard::report,this, &g_id);
}

SystemGuard::SystemGuard(const SystemGuard& guard)
{
    ;
}

SystemGuard::~SystemGuard(){
    is_stop = true;
    if (doing_.joinable())
    {
        doing_.join();
    }
}


float SystemGuard::charge(float money, Order* order)
{
    float delat = money - order->GetSpend();
    return delat;
}

bool is_car_exist(std::string& plate) 
{
    std::fstream file;
    file.open("../data/car.txt");
    bool res = false;
    if (file.is_open()) {
        std::string _plate;
        while (std::getline(file, _plate))
        {
            if (_plate.find(plate) != std::string::npos )
            {
                res = true;
                break;
            }
        }
        file.close();
    }
    return res;
}

bool SystemGuard::agree_in_out(std::string& plate)
{
    bool isExist = is_car_exist(plate);
    if (park_num < PARK_MAX && !isExist) {
        std::lock_guard<std::mutex> lock(Manager::mtx_);
        park_num += 1;
    } else if(park_num <= PARK_MAX && isExist){
        std::lock_guard<std::mutex> lock(Manager::mtx_);
        park_num -= 1;
        delete_car(plate);  
    }
    return (park_num <= PARK_MAX);
}

void SystemGuard::report(int* id)
{
    while(is_stop == false) 
    {
        std::fstream file;
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm* time = std::localtime(&t);
        file.open("../data/order.txt");
        bool isOuttime = false;
        if (file.is_open()) 
        {
            std::string line;
            while (std::getline(file, line)){
                int nextIdx = line.find("remark");
                int preIdx = line.find_last_of("-") + 1;
                int in_time = std::stoi(line.substr(preIdx, nextIdx));
                isOuttime = (time->tm_hour - in_time > 5);
                nextIdx = line.find("plate");
                preIdx = line.find("orderID:") + 
                    std::string("orderID:").size();
                *id = std::stoi(line.substr(preIdx, nextIdx));
                if (isOuttime) 
                {
                    break;
                }
            }
            file.close();
        } else {
            std::cout << "report order system error" << std::endl;
        }
        if (isOuttime) {
            std::unique_lock<std::mutex> lock(Manager::report_cond_mtx_);
            Manager::report_cond_.notify_all();
        }
    }
    return;
}