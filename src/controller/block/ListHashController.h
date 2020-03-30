#ifndef LIST_HASH_CONTROLLER_H
#define LIST_HASH_CONTROLLER_H

#include "../BaseController.h"

class ListHashController: public BaseController {
public:
    ListHashController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};
#endif // LIST_HASH_CONTROLLER_H
