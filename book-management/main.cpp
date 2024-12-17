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

    rabbitMQ.consume("ListBooks", [&](const std::string_view &body, uint64_t deliveryTag, bool redelivered) {
        try {
            std::cout << "[ListBooks] Received request: " << body << std::endl;
            auto jsonMessage = nlohmann::json::parse(body);

            if (jsonMessage.contains("action") && jsonMessage["action"] == "list-books") {
                std::cout << "[ListBooks] Action: list-books" << std::endl;
                bookManagementService.GetAllBooks();

                nlohmann::json responseJson;
                responseJson["status"] = "success";
                RabbitMQAdapter::getInstance().sendMessage("ListBooksResponse", responseJson.dump());
                std::cout << "[ListBooks] Response sent successfully" << std::endl;
                RabbitMQAdapter::getInstance().ack(deliveryTag);
            } else {
                std::cerr << "[ListBooks] Invalid action received or missing action key" << std::endl;
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
