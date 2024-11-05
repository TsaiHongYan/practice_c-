#include <iostream>

class Customer
{
    public:
        void park_in();
        void park_out();
    private:
        std::string plat_num_;
        std::string flag_;
};

class OutCarOwner: public Customer
{
    public:
        void pay();
};

class InCarOwner: public Customer
{
    public :
        void swing();
    private:
        int age_;
        std::string name_;
        std::string ID_;
        int tel_;
};

class SpecCarOwner:public Customer
{
    public:
        void remark();
};