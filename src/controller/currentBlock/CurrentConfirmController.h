#ifndef CONFIRMCONTROLLER_H
#define CONFIRMCONTROLLER_H
#include "../BaseController.h"

class CurrentConfirmController: public BaseController {
    Q_OBJECT
    Q_DISABLE_COPY(CurrentConfirmController)
public:
    CurrentConfirmController();
    void service(HttpRequest &request, HttpResponse &response);
};
#endif // CONFIRMCONTROLLER_H
