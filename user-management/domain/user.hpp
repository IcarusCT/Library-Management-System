//
// Created by elif on 12/10/24.
//

#ifndef USER_HPP
#define USER_HPP
#include <string>
#include <nlohmann/json.hpp>

class User {
public:
    std::string _id;

    std::string username;

    std::string password;

    User()=default;

    User(const std::string &id, const std::string &username, const std::string &password)
    : _id(id), username(username), password(password) {}

};


#endif //USER_HPP
