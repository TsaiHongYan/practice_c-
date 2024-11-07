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
void SystemManager::operator -(std::string& plate)
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
bool SystemGuard::agree_in_out(std::string& plate)
{
    return;
}

void SystemGuard::report()
{
    return;
}