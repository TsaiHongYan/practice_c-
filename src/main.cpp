#include <iostream>
#include <fstream>
#include <memory>
#include <actor.h>
#include <customer.h>
#include <info.h>
/*----------------------------------------------------------------------------*/
systemManager create_manager(std::fstream& file)
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
    file<<"wordID:"<< wordID <<"name:"<<name<<"age"<< age
        <<"address" << address << "tel" << tel << " mode:1,worktime:"
        << worktime <<std::endl;
    systemManager manager(age, name, address, wordID, tel, 1, worktime);
    return manager;
}

systemGuard create_guard(std::fstream& file)
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
    file<<"wordID:"<< wordID <<"name:"<<name<<"age"<< age
        <<"address" << address << "tel" << tel << " mode:0,worktime:"
        << worktime <<std::endl;
    systemGuard guard(age, name, address, wordID, tel, 1, worktime);
    return guard;
}


int main()
{
    std::fstream managerFile;
    managerFile.open("manager.txt");
    systemGuard* guardPtr = nullptr;
    if (managerFile.is_open())
    {
        
        std::string item;
        std::getline(managerFile,item);
        /* No manager */
        if (item.empty() ||  item.find("mode:1") == std::string::npos) {
            std::cout << "A new system. Please add manager" << std::endl;
            std::cout << "Y or N " << std::endl;
            char inChar;
            std::cin >> inChar;
            if (inChar == 'Y' || inChar == 'y')
            {
               systemManager manager = 
                    create_manager(managerFile);
                std::cout << "Please add guard" << std::endl;
                systemGuard guard = create_guard(managerFile);
                guardPtr = &guard;
            }
        } else {
            std::cout << "Please Log in" << std::endl;
            std::cout << "Please input your wordID" <<std::endl;
            std::string wordID;
            std::cin >> wordID;
            std::string item;
            std::getline(managerFile,item);
            if (item.find(wordID) != std::string::npos)
            {
                int preIdx = item.find("name");
                int nextIdx = item.find("age");
                std::string name = item.substr(preIdx, nextIdx);
                preIdx = nextIdx;
                nextIdx = item.find("address");
                int age = std::stoi(item.substr(preIdx, nextIdx));
                preIdx = nextIdx;
                std::string address;
                nextIdx = item.find("tel");
                address = item.substr(preIdx, nextIdx);
                preIdx = nextIdx;
                nextIdx = item.find("worktime");
                int tel = std::stoi(item.substr(preIdx, nextIdx));
                nextIdx = item.find("worktime");
                std::string worktime = item.substr(nextIdx, item.size());
                systemGuard guard(age, name, address, wordID, tel, 0, worktime);
                guardPtr = &guard;
            } 
        }
        while(1){
            std::string keyword;
            std::cin >> keyword;
            if (keyword.compare("q") == 0 || keyword.compare("Q"))
            {
                break;
            }
        }
    } 
    /* */
    managerFile.close();
    return 0;
}