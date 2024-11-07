#include <iostream>


enum class order_status{
    PARK_DONE,
    PARK_ERROR,
    PARK_ING
};

class Order {
    public:
        Order(std::string& plate);
        float GetSpend();
        ~Order();
    private:
        std::string flag_;
        std::string plate_;
        order_status status_;
        std::tm* in_time_;
        std::tm* out_time_;
        float cost_money_;
        std::string remark_;
        int orderID_;
};
