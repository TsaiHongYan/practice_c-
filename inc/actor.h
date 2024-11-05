#include <iostream>
/*----------------------------------------------------------------------------*/
class Manager
{    
    public:
        Manager(int age, std::string &name, std::string& address,
            std::string& wordID, int tel, int mode, std::string& worktime):
            age_(age),name_(name),address_(address),wordID_(wordID),
             tel_(tel),mode_(mode),worktime_(worktime){};
    private:
        int age_;
        std::string name_;
        std::string address_;
        std::string wordID_;
        int tel_;
        int mode_;
        std::string worktime_;
};

class systemGuard : public Manager
{
    public:
    using Manager::Manager;
    float charge(float money);
    void consult();
    bool agree_in_out();
    void remark();
    void report();
};

class systemManager :public Manager
{
    public:
    using Manager::Manager;
    void operator +(systemGuard& guard);
    void operator -(systemGuard& guard);
    void operator +(std::string& plate);
    void operator -(std::string& plate);
    void check();
    void handlingExceptions();
};