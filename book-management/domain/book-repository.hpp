//
// Created by elif on 12/10/24.
//

#ifndef BOOK_REPOSITORY_HPP
#define BOOK_REPOSITORY_HPP
#include <mongocxx/client.hpp>
#include <mongocxx/collection.hpp>
#include <../libs/cpp-bson-convert.hpp>

#include "book-factory.hpp"
#include "book.hpp"

class BookRepository {

public:
    BookRepository()
        : client(mongocxx::uri{"mongodb://localhost:27017"}),
          collection(client["library"]["books"]) {
    }
    void insertBook(const bsoncxx::document::value &book) {
        collection.insert_one({book});
    }

    void deleteBook(const bsoncxx::document::value &book) {
        collection.delete_one({book});
    }

    std::vector<Book> listAllBooks() {
        std::vector<Book> persons;
        auto cursor = collection.find({});
        return factory.createListFromDB(cursor);
    }

private:
    mongocxx::client client;
    mongocxx::collection collection;
    BookFactory factory;
};


#endif //BOOK_REPOSITORY_HPP
