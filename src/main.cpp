#include <iostream>
#include <fstream>
#include <memory>
#include <manager.h>
#include <customer.h>
#include <order.h>
/*----------------------------------------------------------------------------*/
SystemManager create_manager(std::fstream& file)
{
    std::cout << "Please input age " << std::endl;
     int age = 23;
    
    std::cout << "Please input name" << std::endl;
     std::string name("wang");
    
    std::cout << "Please input address " << std::endl;
     std::string address("liao");
    
    std::cout << "Please input word ID " << std::endl;
     std::string wordID("A123");
    
    std::cout << "Please input tel " << std::endl;
     int tel = 982;

    std::cout << "Please input worktime" << std::endl;
     std::string worktime("3");

    file<<"wordID:"<< wordID <<"name:"<<name<<"age"<< age
        <<"address" << address << "tel" << tel << " mode:1,worktime:"
        << worktime << "\n";

    SystemManager manager(age, name, address, wordID, tel, 1, worktime);
    return manager;
}

SystemGuard create_guard(std::fstream& file)
{
    std::cout << "Please input age " << std::endl;
    int age = 22;
    std::cout << "Please input name" << std::endl;
    std::string name("li");
    std::cout << "Please input address " << std::endl;
    std::string address("yue");
    std::cout << "Please input word ID " << std::endl;
    std::string wordID("B123");
    std::cout << "Please input tel " << std::endl;
     int tel = 981;
    std::cout << "Please input worktime" << std::endl;
    std::string worktime("3");
    file<<"wordID:"<< wordID <<"name:"<<name<<"age"<< age
        <<"address" << address << "tel" << tel << " mode:0,worktime:"
        << worktime << "\n";

    SystemGuard guard(age, name, address, wordID, tel, 1, worktime);
    return guard;
}


int main()
{
    std::fstream managerFile;
    managerFile.open("../data/manager.txt");
    SystemGuard* guardPtr = nullptr;
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
               SystemManager manager = 
                    create_manager(managerFile);
                std::cout << "Please add guard" << std::endl;
                SystemGuard guard = create_guard(managerFile);
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
                std::string worktime = item.substr(nextIdx, item.size());
                SystemGuard guard(age, name, address, wordID, tel, 0, worktime);
                guardPtr = &guard;
            } 
        }
        OutCarOwner customer;
        std::string plane = customer.park_in();
        guardPtr->agree_in_out(plane);
        Order order(plane);
        guardPtr->agree_in_out(plane);
        float cost = customer.pay(&order);
        float charge = guardPtr->charge(cost , &order);
        std::cout << "charge " << charge << std::endl;
        while(1){
            std::string keyword;
            std::cin >> keyword;
            if (keyword.compare("q") == 0 || keyword.compare("Q") == 0)
            {
                break;
            }
        }
    } 
    managerFile.close();
    return 0;
}