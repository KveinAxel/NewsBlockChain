#ifndef INFOCONTROLLER_H
#define INFOCONTROLLER_H

#include "../BaseController.h"

class CurrentInfoController: public BaseController {
    Q_OBJECT
    Q_DISABLE_COPY(CurrentInfoController)
public:
    CurrentInfoController();
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // INFOCONTROLLER_H
