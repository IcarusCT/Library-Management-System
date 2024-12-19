//
// Created by elif on 12/10/24.
//

#ifndef USER_MANAGEMENT_SERVICE_HPP
#define USER_MANAGEMENT_SERVICE_HPP
#include "../domain/user-service.hpp"
#include <map>
#include <functional>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include "../user-dto/request/add-user-request.hpp"
#include "../user-dto/user-dto-assembler.hpp"

using json = nlohmann::json;

class UserManagementService {
public:
    UserManagementService(UserService& service) : userService(service) {}

    void HandleAction(const std::string &action, const json &payload) {
        if (actionHandlers.count(action)) {
            actionHandlers[action](payload);
        } else {
            std::cerr << "Unknown action: " << action << std::endl;
        }
    }

    void AddUser(const AddUserRequest& request) {
        std::cout << "Adding user: " << request.name << request.surname << std::endl;
        userService.addUser(request.name, request.surname, request.phone, request.username, request.password);
        std::cout << "Added user: " << request.name << request.surname << std::endl;
    }
private:
    UserService& userService;
    std::map<std::string, std::function<void(const nlohmann::json &)> > actionHandlers;


};



#endif //USER_MANAGEMENT_SERVICE_HPP
