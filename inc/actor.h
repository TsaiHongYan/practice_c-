#include <iostream>
#include <order.h>
/*----------------------------------------------------------------------------*/
class Manager
{    
    public:
        Manager(int age, std::string &name, std::string& address,
            std::string& wordID, int tel, int mode, std::string& worktime):
            age_(age),name_(name),address_(address),wordID_(wordID),
             tel_(tel),mode_(mode),worktime_(worktime){};
        virtual ~Manager(){};
    private:
        int age_;
        std::string name_;
        std::string address_;
        std::string wordID_;
        int tel_;
        int mode_;
        std::string worktime_;
        constexpr Order orderPtr;
        static int park_num = 0;
};

class SystemGuard : public Manager
{
    public:
        using Manager::Manager;
        float charge(float money);
        void consult();
        bool agree_in_out(std::string& plate);
        void report();
};

class SystemManager :public Manager
{
    public:
    using Manager::Manager;
    void operator +(std::string& plate);
    void operator -(std::string& plate);
    void check();
    void handlingExceptions();
};