#include <iostream>
#include <fstream>
#include <vector>
#include <actor.h>
/*----------------------------------------------------------------------------*/

void systemManager::operator +(systemGuard& guard)
{
    
    return; 
}
void systemManager::operator -(systemGuard& guard)
{
    return; 
}

void systemManager::operator +(std::string& plate)
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
void systemManager::operator -(std::string& plate)
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
void systemManager::check()
{
    return; 
}
void systemManager::handlingExceptions()
{
    return; 
}


float systemGuard::charge(float money)
{
    return 0.0f;
}
void systemGuard::consult()
{
    return;
}
bool systemGuard::agree_in_out()
{
    return;
}
void systemGuard::remark()
{
    return;
}
void systemGuard::report()
{
    return;
}