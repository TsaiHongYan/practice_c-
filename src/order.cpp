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
    std::fstream file;
    file.open("order.txt");
    if (file.is_open()) {
        file << "orderID:"<<orderID_ << "plate:"<< plate_
              <<"in time:"<< in_time_->tm_year << "-" << 
              "-" << in_time_->tm_mon <<
              "-" << in_time_->tm_mday << 
              " " << in_time_->tm_hour<< 
              "remark:"<< remark_<< std::endl;
        file.close();
    } else {
        std::cout << "order system error" << std::endl;
    }
}


float Order::GetSpend()
{
    // std::string flag_;
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    out_time_ = std::localtime(&t);
    int delta_hour = out_time_->tm_hour  - in_time_->tm_hour;
    if (delta_hour == 0) {
        cost_money_ = 5.0;
    } else {
        cost_money_ = delta_hour * 5.0f;
    }
    return cost_money_;
}

int Order::GetOrderID()
{
    return orderID_;
}

Order::~Order() {

}