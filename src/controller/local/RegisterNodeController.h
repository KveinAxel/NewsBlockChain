#ifndef NEWS_BLOCK_CHAIN_REGISTERNODECONTROLLER_H
#define NEWS_BLOCK_CHAIN_REGISTERNODECONTROLLER_H
#include <controller/BaseController.h>

class RegisterNodeController: public BaseController {
public:
    RegisterNodeController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};


#endif //NEWS_BLOCK_CHAIN_REGISTERNODECONTROLLER_H
