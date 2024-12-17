//
// Created by elif on 12/13/24.
//

#ifndef ADD_BOOK_REQUEST_HPP
#define ADD_BOOK_REQUEST_HPP
#include <string>
#include <nlohmann/json.hpp>


class AddBookRequest {
    public:
    std::string title;
    std::string author;

    AddBookRequest() = default;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(AddBookRequest, title, author)

};



#endif //ADD_BOOK_REQUEST_HPP
