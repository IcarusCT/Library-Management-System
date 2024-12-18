#include <nlohmann/json.hpp>
#include "../libs/rabbit-mq-adapter.hpp"
#include "application/book-management-service.hpp"
#include "library-dto/request/add-book-request.hpp"

using json = nlohmann::json;

BookFactory bookFactory;
BookRepository bookRepository;
BookService bookService{bookRepository, bookFactory};
BookManagementService bookManagementService(bookService);


int main() {
    RabbitMQAdapter &rabbitMQ = RabbitMQAdapter::getInstance();
    rabbitMQ.init("amqp://guest:guest@localhost/");

    rabbitMQ.consume("AddBook", [&](const std::string_view &body, uint64_t deliveryTag, bool redelivered) {
        try {
            std::cout << "[AddBook] Received request: " << body << std::endl;
            auto jsonMessage = nlohmann::json::parse(body);

            AddBookRequest request = jsonMessage.get<AddBookRequest>();
            std::cout << "[AddBook] Adding book: " << request.title << " by " << request.author << std::endl;

            bookManagementService.AddBook(request);
            RabbitMQAdapter::getInstance().ack(deliveryTag);
        } catch (const std::exception &e) {
            std::cerr << "[AddBook] Error: " << e.what() << std::endl;
        }
    });

    rabbitMQ.consume("ListBooksRequest", [&](const std::string_view &body, uint64_t deliveryTag, bool redelivered) {
        try {
            std::cout << "[ListBooks] Received request: " << body << std::endl;

            auto jsonMessage = nlohmann::json::parse(body);

            if (jsonMessage.contains("action") && jsonMessage["action"] == "list-books") {
                std::cout << "[ListBooks] Action: list-books" << std::endl;

                auto books = bookManagementService.GetAllBooks();

                nlohmann::json booksJson = nlohmann::json::array();
                for (const auto &book: books) {
                    nlohmann::json bookJson;
                    bookJson["title"] = book.title;
                    bookJson["author"] = book.author;
                    booksJson.push_back(bookJson);
                }
                nlohmann::json responseJson;
                responseJson["action"] = "list-books";
                responseJson["paylaod"] = booksJson;
                responseJson["status"] = "success";

                RabbitMQAdapter::getInstance().sendMessage("ListBooksResponse", responseJson.dump());
                std::cout << "[Microservice] Response sent to Aggregator: " << responseJson.dump() << std::endl;


                RabbitMQAdapter::getInstance().ack(deliveryTag);
            } else {
                std::cerr << "[ListBooks] Invalid action received or missing action key in message: " << body <<
                        std::endl;
                RabbitMQAdapter::getInstance().ack(deliveryTag);
            }
        } catch (const std::exception &e) {
            std::cerr << "[ListBooks] Error: " << e.what() << std::endl;
            RabbitMQAdapter::getInstance().ack(deliveryTag);
        }
    });


    rabbitMQ.start();

    return 0;
}
