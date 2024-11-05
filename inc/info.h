#include <iostream>
enum class info_status{
    PARK_DONE,
    PARK_ERROR,
    PARK_ING
};

class info {
    public:
        void create();
        void destroy();
        void find();
        void park();
        void reserve();
    private:
        std::string flag;
        std::string plate;
        info_status status;
        std::string in_time;
        std::string out_time;
        std::string cost_money;
        std::string remark;
        int park_num;
};
