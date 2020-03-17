#ifndef CONFIRMCONTROLLER_H
#define CONFIRMCONTROLLER_H

#include "../BaseController.h"

class ConfirmController: public BaseController {
    Q_OBJECT
    Q_DISABLE_COPY(ConfirmController)
public:
    ConfirmController();
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // CONFIRMCONTROLLER_H
