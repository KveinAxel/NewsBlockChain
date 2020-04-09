#include "SearcherService.h"

Message<std::vector<std::string>> SearcherService::search(std::vector<std::string> keywords) {
    return Message<std::vector<std::string>>::success("成功");
}
