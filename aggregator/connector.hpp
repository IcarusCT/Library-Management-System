#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP

#include <string>
#include <nlohmann/json.hpp>
#include "rabbit-mq-adapter.hpp"

class Connector {
public:
    Connector() {
        RabbitMQAdapter &rabbitMQ = RabbitMQAdapter::getInstance();
        rabbitMQ.init("amqp://guest:guest@localhost:5672");
    }

    void addBook(const nlohmann::json &payload) {
        std::cout << "Processing AddBook..." << std::endl;
        sendToMicroservice("AddBook", payload.dump());
    }

    void deleteBook(const nlohmann::json &payload) {
        std::cout << "Processing DeleteBook..." << std::endl;
        sendToMicroservice("DeleteBook", payload.dump());
    }

    void listBooks() {
        std::cout << "Processing ListBooks..." << std::endl;
        nlohmann::json payload;
        payload["action"] = "list-books";
        sendToMicroservice("ListBooks", payload.dump());
    }


    void handleApiRequest( const std::string &action, const nlohmann::json &payload) {
        std::string queueName;

        if (action == "add-book") {
            addBook(payload);
        } else if (action == "delete-book") {
            deleteBook(payload);
        } else if (action == "list-books") {
            listBooks();
        } else {
            std::cerr << "Unknown action: " << action << std::endl;
        }
    }

    void sendToMicroservice(const std::string &queueName, const std::string &message) {
        std::cout << "Sending to microservice (queue: " << queueName << "): " << message << std::endl;
        RabbitMQAdapter::getInstance().sendMessage(queueName, message);
    }

    void getFromApiGateway(const std::string &queueName, const RabbitMQAdapter::MessageCallback &callback) {
        std::cout << "Getting from API Gateway (" << queueName << ")" << std::endl;
        RabbitMQAdapter::getInstance().consume(queueName, callback);
    }
};

#endif // CONNECTOR_HPP
