#ifndef CONFIRM_CONTROLLER_H
#define CONFIRM_CONTROLLER_H

#include "../BaseController.h"

class ConfirmController: public BaseController {
public:
    ConfirmController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};

#endif // CONFIRM_CONTROLLER_H
