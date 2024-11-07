#include <iostream>
#include <fstream>
#include <vector>
#include <actor.h>

/*----------------------------------------------------------------------------*/

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
    return; 
}
void SystemManager::handlingExceptions()
{
    
    return; 
}


float SystemGuard::charge(float money)
{
    float delat = money - order_.GetSpend();
    return 0.0f;
}
void SystemGuard::consult()
{
    return;
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
    if (Manager::park_num < PARK_MAX && !isExist) {
        std::lock_guard<std::mutex> lock(Manager::mtx);
        Manager::park_num += 1;
    } else if(Manager::park_num <= PARK_MAX && isExist){
        std::lock_guard<std::mutex> lock(Manager::mtx);
        Manager::park_num -= 1;
        delete_car(plate);
    }
    return (Manager::park_num <= PARK_MAX);
}

void SystemGuard::report()
{
    return;
}