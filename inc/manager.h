#ifndef INC_MANAGER_H
#define INC_MANAGER_H
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <functional>
#include <order.h>
/*----------------------------------------------------------------------------*/
#define PARK_MAX (10)
class Manager
{    
    public:
        Manager(int age, std::string &name, std::string& address,
            std::string& wordID, int tel, int mode, std::string& worktime):
            age_(age),name_(name),address_(address),wordID_(wordID),
             tel_(tel),mode_(mode),worktime_(worktime){
            };
        Manager() = default;
        virtual ~Manager(){
            ;
        };
    protected:
        int age_;
        std::string name_;
        std::string address_;
        std::string wordID_;
        int tel_;
        int mode_;
        std::string worktime_;
        std::thread doing_;
        static std::mutex mtx_;
        static std::mutex report_cond_mtx_;
        static std::condition_variable report_cond_;
};

class SystemGuard : public Manager
{
    public:
        SystemGuard(int age, std::string &name, std::string& address,
            std::string& wordID, int tel, int mode, std::string& worktime);
        SystemGuard(const SystemGuard& guard);
        float charge(float money, Order* order);
        bool agree_in_out(std::string& plate);
        ~SystemGuard(){
            if (doing_.joinable())
             {
                doing_.join();
             }
        }
    private:
        void report(int* id);
};

class SystemManager : public Manager
{
    public:
        SystemManager(int age, std::string &name, std::string& address,
                std::string& wordID, int tel, int mode, std::string& worktime);
        SystemManager(const SystemManager& manager);
        void operator +(std::string& plate);
        void operator -(std::string& plate);
        void handlingExceptions(int orderID);
        ~SystemManager (){
            if (doing_.joinable())
             {
                doing_.join();
             }
        }
    private :
        void check(int id);
};
#endif