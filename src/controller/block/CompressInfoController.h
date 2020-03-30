#ifndef COMPRESS_INFO_CONTROLLER_H
#define COMPRESS_INFO_CONTROLLER_H

#include "../BaseController.h"

class CompressInfoController: public BaseController {
public:
    CompressInfoController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};


#endif // COMPRESS_INFO_CONTROLLER_H
