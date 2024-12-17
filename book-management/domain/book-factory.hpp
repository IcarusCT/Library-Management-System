//
// Created by elif on 12/10/24.
//

#ifndef BOOK_FACTORY_HPP
#define BOOK_FACTORY_HPP
#include "book.hpp"
#include "../libs/cpp-bson-convert.hpp"
#include <bsoncxx/v_noabi/bsoncxx/document/view.hpp>
#include <bsoncxx/v_noabi/bsoncxx/document/value.hpp>
#include <bsoncxx/v_noabi/bsoncxx/builder/basic/document.hpp>

class BookFactory {
public:
    BookFactory() = default;

    bsoncxx::document::value createDocumentForDB(const std::string &title, const std::string &author) {
        return Book::toBSON(Book{title, author});
    }

    static Book createDocumentFromDB(const bsoncxx::document::value &bookDoc, const std::string &title, const std::string &author) {
            Book book;
            return Book::fromBSON(bookDoc.view());
        }

    static std::vector<Book> createListFromDB(mongocxx::cursor &cursor) {
        std::vector<Book> books;
        for (const auto& doc : cursor) {
            Book book;
            Book::fromBSON(doc);
            books.push_back(book);
        }

        return books;
    }
};


#endif //BOOK_FACTORY_HPP
