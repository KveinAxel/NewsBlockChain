#ifndef COMPRESSINFOCONTROLLER_H
#define COMPRESSINFOCONTROLLER_H

#include "../BaseController.h"

class CurrentCompressInfoController: public BaseController {
    Q_OBJECT
    Q_DISABLE_COPY(CurrentCompressInfoController)
public:
    CurrentCompressInfoController();
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // COMPRESSINFOCONTROLLER_H
