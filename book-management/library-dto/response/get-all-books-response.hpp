//
// Created by elif on 12/16/24.
//

#ifndef GET_ALL_BOOKS_RESPONSE_HPP
#define GET_ALL_BOOKS_RESPONSE_HPP
#include <nlohmann/json.hpp>
#include <vector>
#include <bsoncxx/v_noabi/bsoncxx/oid.hpp>
#include <bsoncxx/v_noabi/bsoncxx/document/view.hpp>
#include <bsoncxx/v_noabi/bsoncxx/types.hpp>

class GetAllBooksResponse {
public:
    struct Book {
        std::optional<bsoncxx::v_noabi::oid> _id;
        std::string title;
        std::string author;

        Book() = default;

        Book(const std::string &title, const std::string &author)
            : title(title), author(author) {
        }

        NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Book, title, author)
    };

    GetAllBooksResponse() = default;

    GetAllBooksResponse(const std::vector<Book> &books) : books(books) {
    }

    const std::vector<Book> &getBooks() const { return books; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(GetAllBooksResponse, books);

    std::vector<Book> books;
};


#endif //GET_ALL_BOOKS_RESPONSE_HPP
