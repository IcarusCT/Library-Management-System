//
// Created by elif on 12/10/24.
//

#ifndef USER_REPOSITORY_HPP
#define USER_REPOSITORY_HPP
#include <mongocxx/client.hpp>
#include <mongocxx/collection.hpp>
#include <../libs/cpp-bson-convert.hpp>

#include "user-factory.hpp"


class UserRepository {
public:
    UserRepository()
            : client(mongocxx::uri{"mongodb://localhost:27017"}),
              collection(client["library"]["users"]) {
    }

    void insertUser(const bsoncxx::document::value &user) {
        collection.insert_one({user});
    }



private:
    mongocxx::client client;
    mongocxx::collection collection;
    UserFactory factory;
};



#endif //USER_REPOSITORY_HPP
