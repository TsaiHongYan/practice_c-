#include <iostream>
#include <fstream>
#include <memory>
#include <actor.h>
#include <customer.h>
#include <info.h>
/*----------------------------------------------------------------------------*/
std::shared_ptr<Manager> create_manager(FILE* file)
{
    std::cout << "Please input age " << std::endl;
    int age;
    std::cin >> age;
    std::cout << "Please input name" << std::endl;
    std::string name;
    std::cin >> name;
    std::cout << "Please input address " << std::endl;
    std::string address;
    std::cin >> address;
    std::cout << "Please input word ID " << std::endl;
    std::string wordID;
    std::cin >> wordID;
    std::cout << "Please input tel " << std::endl;
    int tel;
    std::cin >> tel;
    std::cout << "Please input worktime" << std::endl;
    std::string worktime;
    std::cin >> tel;
    fprintf(file, "wordID:%s,name:%s,age:%d,address:%s,tel%d, \
                 mode:1,worktime:%s \n",
            wordID,name,age,address, tel, worktime);
    return std::make_shared<systemManager>(
            age, name, address, wordID, tel, 1, worktime);
}

std::shared_ptr<Manager> create_guard(FILE* file)
{
    std::cout << "Please input age " << std::endl;
    int age;
    std::cin >> age;
    std::cout << "Please input name" << std::endl;
    std::string name;
    std::cin >> name;
    std::cout << "Please input address " << std::endl;
    std::string address;
    std::cin >> address;
    std::cout << "Please input word ID " << std::endl;
    std::string wordID;
    std::cin >> wordID;
    std::cout << "Please input tel " << std::endl;
    int tel;
    std::cin >> tel;
    std::cout << "Please input worktime" << std::endl;
    std::string worktime;
    std::cin >> tel;
    fprintf(file, "wordID:%s,name:%s,age:%d,address:%s,tel%d, \
                 mode:0,worktime:%s \n",
            wordID,name,age,address, tel, worktime);
    return std::make_shared<systemGuard>(
            age, name, address, wordID, tel, 0, worktime);
}


int main()
{
    FILE* managerFile = fopen("manager.txt", "rw");
    std::shared_ptr<Manager> guardPtr = nullptr;
    if (managerFile != nullptr)
    {
        
        constexpr unsigned char buf_size = 100;
        char buffer[buf_size];
        std::string item = fgets(buffer, buf_size, managerFile);
        /* No manager */
        if (item.empty() ||  item.find("mode:1") == std::string::npos) {
            std::cout << "A new system. Please add manager" << std::endl;
            std::cout << "Y or N " << std::endl;
            char inChar;
            std::cin >> inChar;
            if (inChar == 'Y' || inChar == 'y')
            {
                std::shared_ptr<Manager> managerPtr = 
                    create_manager(managerFile);
                std::cout << "Please add guaard" << std::endl;
                guardPtr = create_guard(managerFile);
            }
        } else {
            std::cout << "Please Log in" << std::endl;
            std::cout << "Please input your wordID" <<std::endl;
            std::string wordID;
            std::cin >> wordID;
            std::string item = fgets(buffer, buf_size, managerFile);
            int age;
            std::string name;
            std::string address;
            int tel;
            std::string worktime;
            std::cin >> tel;
            guardPtr = std::make_shared<systemGuard>(
                age, name, address, wordID, tel, 0, worktime);
            
        }
    } 


    /* */
    fclose(managerFile);
    return 0;
}