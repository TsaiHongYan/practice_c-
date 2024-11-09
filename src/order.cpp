#include <iostream>
#include <fstream>
#include <order.h>

/*----------------------------------------------------------------------------*/
static int orderID = 0;
Order::Order(std::string& plate) {
    plate_ = plate;
    status_ = order_status::PARK_ING;
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    in_time_ = std::localtime(&t);
    orderID_ = orderID;
    orderID++;
    /* Visit car.txt*/
    // std::string flag_;
    // std::string out_time_;
    // std::string cost_money_;
    // std::string remark_;
}

float Order::GetSpend()
{
    return cost_money_;
}

int Order::GetOrderID()
{
    return orderID_;
}

Order::~Order() {

}