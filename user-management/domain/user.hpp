//
// Created by elif on 12/10/24.
//

#ifndef USER_HPP
#define USER_HPP
#include <string>
#include <nlohmann/json.hpp>
#include <bsoncxx/v_noabi/bsoncxx/oid.hpp>
#include <cpp-bson-convert.hpp>


class User {
public:
    std::optional<bsoncxx::oid> _id;
    std::string name;
    std::string surname;
    std::string phone;
    std::string username;
    std::string password;

    User() = default;

    User(const std::string &name, const std::string &surname, const std::string &phone, const std::string &username, const std::string &password)
        : name(name), surname(surname), phone(phone), username(username), password(password) {
    }

    BSON_DEFINE_TYPE(User, _id, name, surname, phone, username, password)

};


#endif //USER_HPP
