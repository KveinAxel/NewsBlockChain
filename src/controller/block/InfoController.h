#ifndef INFO_CONTROLLER_H
#define INFO_CONTROLLER_H
#include "../BaseController.h"

class InfoController: public BaseController {
public:
    InfoController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};

#endif // INFO_CONTROLLER_H
