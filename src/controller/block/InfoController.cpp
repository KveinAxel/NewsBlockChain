#include "InfoController.h"

InfoController::InfoController()
= default;

void InfoController::service(const httplib::Request &req, httplib::Response &res) {
    BaseController::service(req, res);
}
