#ifndef COMPRESSINFOCONTROLLER_H
#define COMPRESSINFOCONTROLLER_H

#include "../BaseController.h"

class CompressInfoController: public BaseController {
    Q_OBJECT
    Q_DISABLE_COPY(CompressInfoController)
public:
    CompressInfoController();
    void service(HttpRequest &request, HttpResponse &response);
};


#endif // COMPRESSINFOCONTROLLER_H
