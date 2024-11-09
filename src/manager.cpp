#include <iostream>
#include <fstream>
#include <vector>
#include <manager.h>

/*----------------------------------------------------------------------------*/
static int park_num = 0;
std::mutex Manager::mtx_;
std::mutex Manager::report_cond_mtx_;
std::condition_variable Manager::report_cond_;

SystemManager::SystemManager(int age, std::string &name, std::string& address, 
    std::string& wordID, int tel, int mode, std::string& worktime): 
Manager(age, name, address, wordID, tel, mode, worktime)
{
    doing_ = std::thread(check);
}

void SystemManager::operator +(std::string& plate)
{
    std::ofstream file;
    file.open("car.txt");
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
    file.open("car.txt");
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

void SystemManager::check()
{
    Order order;
    while(true) {
        std::unique_lock<std::mutex> lock(Manager::report_cond_mtx_);
        Manager::report_cond_.wait(lock);
        handlingExceptions(order);
    } 
    return; 
}

void SystemManager::handlingExceptions(Order& order)
{
    std::fstream file;
    file.open("order.txt");
    if (file.is_open()) {
        std::string  the_order;
        std::vector<std::string> lines;
        while (std::getline(file, the_order))
        {
            int orderID = order.GetOrderID();
            std::string  str_orderID = std::to_string(orderID);
            if (the_order.find(str_orderID) != std::string::npos )
            {
                lines.push_back(str_orderID);
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

SystemGuard::SystemGuard(int age, std::string &name, std::string& address, 
    std::string& wordID, int tel, int mode, std::string& worktime): 
Manager(age, name, address, wordID, tel, mode, worktime)
{
    doing_ = std::thread(report);
}
float SystemGuard::charge(float money, Order* order)
{
    float delat = money - order->GetSpend();
    return delat;
}

bool is_car_exist(std::string& plate) 
{
    std::fstream file;
    file.open("car.txt");
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
        if (false) 
        {
            ;
        } else {
            std::lock_guard<std::mutex> lock(Manager::mtx_);
            park_num -= 1;
            delete_car(plate);
        }
    }
    return (park_num <= PARK_MAX);
}

void SystemGuard::report()
{
    std::unique_lock<std::mutex> lock(Manager::report_cond_mtx_);
    Manager::report_cond_.notify_all();
    return;
}