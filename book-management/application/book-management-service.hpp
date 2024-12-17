//
// Created by elif on 12/10/24.
//

#ifndef BOOK_MANAGEMENT_SERVICE_HPP
#define BOOK_MANAGEMENT_SERVICE_HPP
#include "../domain/book-service.hpp"
#include <map>
#include <functional>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include "../library-dto/request/add-book-request.hpp"
#include "../library-dto/library-dto-assembler.hpp"

class AddBookRequest;
using json = nlohmann::json;

class BookManagementService {
public:
    BookManagementService(BookService& service) : bookService(service) {}

    void HandleAction(const std::string &action, const json &payload) {
        if (actionHandlers.count(action)) {
            actionHandlers[action](payload);
        } else {
            std::cerr << "Unknown action: " << action << std::endl;
        }
    }

    void AddBook(const AddBookRequest& request) {
        std::cout << "Adding book: " << request.title << " by " << request.author << std::endl;
        bookService.addBook(request.title, request.author);
        std::cout << "Added book: " << request.title << " by " << request.author << std::endl;
    }

    std::vector<Book> GetAllBooks() {
        std::vector<Book> allBooks = bookService.getAllBooks();

        GetAllBooksResponse response = LibraryDtoAssembler::toGetAllBooksResponse(allBooks);

        for (const auto& book : response.books) {
            std::cout << "Book Title: " << book.title << ", Author: " << book.author << std::endl;
        }
        return allBooks;
    }


private:
    std::map<std::string, std::function<void(const json &)> > actionHandlers;
    BookService bookService;
};


#endif //BOOK_MANAGEMENT_SERVICE_HPP
