#include <service/searcher/SearcherService.h>
#include "SearchBlocksController.h"

SearchBlocksController::SearchBlocksController()
= default;

void SearchBlocksController::service(const httplib::Request &req, httplib::Response &res) {
    if (req.has_param("keywords")) {
        std::string json = req.get_param_value("keywords");
        rapidjson::Value resValue;
        resValue.SetObject();
        rapidjson::Document document;
        document.Parse(json.c_str());
        if (document.IsArray()) {
            std::vector<std::string> keywords;
            for (auto itr = document.Begin(); itr != document.End(); ++itr) {
                keywords.push_back(itr->GetString());
            }
            auto msg = SearcherService::search(keywords);
            if (msg.code == 200) {
                auto data = msg.data;
                rapidjson::Value arr(rapidjson::kArrayType);
                if (data != nullptr) {
                    for (auto article: *data) {
                        arr.PushBack(rapidjson::Value(article.c_str(), document.GetAllocator()).Move(),
                                     document.GetAllocator());
                    }
                    delete data;
                }
                resValue.AddMember("message", "查询成功", document.GetAllocator());
                resValue.AddMember("data", arr, document.GetAllocator());
                result(res, resValue);
            } else {
                error(res, "400", "查询失败");
            }
        } else {
            error(res, "400", "参数异常");
        }
    } else {
        error(res, "400", "请求参数异常");
    }
}


