//
// Created by elif on 12/10/24.
//

#ifndef USER_FACTORY_HPP
#define USER_FACTORY_HPP
#include "user.hpp"
#include <bsoncxx/v_noabi/bsoncxx/document/view.hpp>
#include <bsoncxx/v_noabi/bsoncxx/document/value.hpp>
#include <cpp-bson-convert.hpp>
#include <mongocxx/v_noabi/mongocxx/cursor.hpp>

class UserFactory {
public:
    UserFactory() = default;

    bsoncxx::document::value createDocumentForDB(const std::string &name, const std::string &surname, const std::string &phone, const std::string &username, const std::string &password) {
        return User::toBSON(User{name, surname, phone, username, password});
    }

    static User createDocumentFromDB(const bsoncxx::document::value &userDoc, const std::string &name, const std::string &surname, const std::string &phone, const std::string &username, const std::string &password) {
        User user;
        return User::fromBSON(userDoc.view());
    }

    static std::vector<User> createListFromDB(mongocxx::cursor &cursor) {
        std::vector<User> users;
        for (const auto& doc : cursor) {
            users.emplace_back(User::fromBSON(doc));
        }

        return users;
    }

};



#endif //USER_FACTORY_HPP
