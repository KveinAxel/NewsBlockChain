#ifndef SEARCHBLOCKSCONTROLLER_H
#define SEARCHBLOCKSCONTROLLER_H

#include "../BaseController.h"

class SearchBlocksController: public BaseController {
    Q_OBJECT
    Q_DISABLE_COPY(SearchBlocksController)
public:
    SearchBlocksController();
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // SEARCHBLOCKSCONTROLLER_H
