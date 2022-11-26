#include <iostream>
#include "http.h"

int main() {
    using namespace httplib;
    Server svr;

    std::map<std::string, std::string> users = {
        {"zippy", "doggy"},
        {"user", "pass"}
    };

    #define METHOD [&](const Request& req, Response& res) 
    svr.set_base_dir("./public");

    svr.Get("/", METHOD {
        res.set_redirect("index.html");
    });

    svr.Get("/auth", [&](const Request& req, Response& res) {
        if(!req.has_param("user") || !req.has_param("pass")) {
            res.set_content("{ error: \"Must include params `user` and `pass`.\"", "application/json");
            return;
        }
        std::string user = req.get_param_value("user");
        std::string pass = req.get_param_value("pass");
        bool is_valid = (users.count(user) > 0) && (users[user] == pass);
        res.set_content("{ valid: " + std::string(is_valid ? "true" : "false") + " }", "application/json");
    });

    svr.listen("0.0.0.0", 8080);

    return 1;

}