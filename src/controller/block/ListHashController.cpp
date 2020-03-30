#include "ListHashController.h"

ListHashController::ListHashController()
= default;

void ListHashController::service(const httplib::Request &req, httplib::Response &res) {
    BaseController::service(req, res);
}

