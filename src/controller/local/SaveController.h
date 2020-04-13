#ifndef NEWS_BLOCK_CHAIN_SAVE_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_SAVE_CONTROLLER_H
#include <controller/BaseController.h>

class SaveController: public BaseController {
public:
    SaveController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};


#endif // NEWS_BLOCK_CHAIN_SAVE_CONTROLLER_H
