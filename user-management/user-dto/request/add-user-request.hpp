//
// Created by elif on 12/19/24.
//

#ifndef ADD_USER_REQUEST_HPP
#define ADD_USER_REQUEST_HPP
#include <string>
#include <nlohmann/json.hpp>

class AddUserRequest {
public:
    std::string name;
    std::string surname;
    std::string phone;
    std::string username;
    std::string password;

    AddUserRequest() = default;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(AddUserRequest, name, surname, phone, username, password)

};



#endif //ADD_USER_REQUEST_HPP
