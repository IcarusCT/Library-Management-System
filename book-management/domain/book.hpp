//
// Created by elif on 12/10/24.
//

#ifndef BOOK_HPP
#define BOOK_HPP
#include <cpp-bson-convert.hpp>
#include <string>
#include <nlohmann/json.hpp>


class Book {
    public:
    std::optional<bsoncxx::oid> _id;
    std::string title;
    std::string author;

    Book()=default;

    Book(const std::string &title, const std::string &author)
        : title(title), author(author) {}


    /*BSON_DEFINE_FROM_BSON(Book, _id, title, author)
    BSON_DEFINE_TO_BSON(Book, _id, title, author)*/

    BSON_DEFINE_TYPE(Book, _id, title, author)

};



#endif //BOOK_HPP
