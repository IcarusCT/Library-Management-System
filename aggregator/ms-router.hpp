#ifndef ROUTER_HPP
#define ROUTER_HPP
#include "connector.hpp"
#include <string>
#include <iostream>
#include "rabbit-mq-adapter.hpp"

class MSRouter {
public:
    static MSRouter &getInstance() {
        static MSRouter instance;
        return instance;
    }

    std::vector<std::string> getServiceForAction(const std::string &action) {
        auto it = actionToServiceMap.find(action);
        if (it != actionToServiceMap.end()) {
            return it->second;
        }
        return {};
    }

private:
    MSRouter() {
        actionToServiceMap["add-book"] = {"bookManagementService.addBook"};
        actionToServiceMap["delete-book"] = {"bookManagementService.deleteBook"};
        actionToServiceMap["list-books"] = {"bookManagementService.getBooks"};
        actionToServiceMap["signup"] = {"userManagementService.signup"};
        actionToServiceMap["login"] = {"userManagementService.login"};
        actionToServiceMap["logout"] = {"userManagementService.logout"};
    }

    std::unordered_map<std::string, std::vector<std::string> > actionToServiceMap;
};

#endif // ROUTER_HPP
