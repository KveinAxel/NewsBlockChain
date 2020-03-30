#include "CompressInfoController.h"

CompressInfoController::CompressInfoController()
= default;

void CompressInfoController::service(const httplib::Request &req, httplib::Response &res) {
    BaseController::service(req, res);
}
