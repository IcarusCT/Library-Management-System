//
// Created by elif on 12/10/24.
//

#ifndef USER_SERVICE_HPP
#define USER_SERVICE_HPP
#include <string>
#include "user-factory.hpp"
#include "user-repository.hpp"

class UserService {
    public:
    UserService(UserRepository& repository, UserFactory& factory) : UserRepository(repository),UserFactory(factory) {}

    void addUser(const std::string &name, const std::string &surname, const std::string &phone, const std::string &username, const std::string &password) {
        const auto userDoc = userFactory.createDocumentForDB(name, surname, phone, username, password);
        userRepository.insertUser(userDoc);
    }

private:
    UserRepository& userRepository;
    UserFactory& userFactory;

};



#endif //USER_SERVICE_HPP
