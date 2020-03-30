#include "SearchBlocksController.h"

SearchBlocksController::SearchBlocksController()
= default;

void SearchBlocksController::service(const httplib::Request &req, httplib::Response &res) {
    BaseController::service(req, res);
}


