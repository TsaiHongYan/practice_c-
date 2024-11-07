#include <iostream>
#include <fstream>
#include <customer.h>
/*----------------------------------------------------------------------------*/
Customer::Customer()
{
    int number = rand();
    number = number % 10;
    plat_num_ = "A0982" + std::to_string(number);
}

std::string Customer::park_in(){
    return plat_num_;
}
std::string Customer::park_out(){
    return plat_num_;
}

float OutCarOwner::pay(Order* order) {
    float money = order->GetSpend() + 
        static_cast<float>(rand() % 10);
    return money;
}

void InCarOwner::swing(){
    return;
}

void SpecCarOwner::remark(){
    return;
}