//
// Created by elif on 12/10/24.
//

#ifndef BOOK_SERVICE_HPP
#define BOOK_SERVICE_HPP
#include <crow/http_response.h>
#include "book-repository.hpp"
#include "book-factory.hpp"
#include "book.hpp"

class BookService {
public:
    BookService(BookRepository& repository, BookFactory& factory) : bookRepository(repository),bookFactory(factory) {}

    void addBook(const std::string &title, const std::string &author) {
            const auto bookDoc = bookFactory.createDocumentForDB(title, author);
            bookRepository.insertBook(bookDoc);
    }

    std::vector<Book> getAllBooks() {
        auto cursor = bookRepository.listAllBooks();
        return cursor;
    }

private:
    BookRepository &bookRepository;
    BookFactory &bookFactory;

};


#endif //BOOK_SERVICE_HPP
