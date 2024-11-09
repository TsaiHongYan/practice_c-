#ifndef INC_CUSTOMER_H
#define INC_CUSTOMER_H
#include <iostream>
#include <order.h>

class Customer
{
    public:
        Customer();
        std::string park_in();
        std::string park_out();
        virtual ~Customer(){};
    protected:
        std::string plat_num_;
        std::string flag_;
};

class OutCarOwner: public Customer
{
    public:
        float pay(Order* order);
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

#endif