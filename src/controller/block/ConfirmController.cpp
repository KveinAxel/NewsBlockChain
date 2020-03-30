#include "ConfirmController.h"

ConfirmController::ConfirmController()
= default;

void ConfirmController::service(const httplib::Request &req, httplib::Response &res) {
    BaseController::service(req, res);
}

