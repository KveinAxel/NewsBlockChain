#ifndef INFOCONTROLLER_H
#define INFOCONTROLLER_H
#include "../BaseController.h"

class InfoController: public BaseController {
    Q_OBJECT
    Q_DISABLE_COPY(InfoController)
public:
    InfoController();
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // INFOCONTROLLER_H
