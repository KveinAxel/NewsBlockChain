#ifndef LISTHASHCONTROLLER_H
#define LISTHASHCONTROLLER_H

#include "../BaseController.h"

class ListHashController: public BaseController {
    Q_OBJECT
    Q_DISABLE_COPY(ListHashController)
public:
    ListHashController();
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // LISTHASHCONTROLLER_H
