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

    void handleAction(const std::string &action, const nlohmann::json &payload) {
        if (action == "add-book") {
            processAction("AddBook", payload, "Processing AddBook...");
        } else if (action == "delete-book") {
            processAction("DeleteBook", payload, "Processing DeleteBook...");
        } else if (action == "list-books") {
            processAction("ListBooksRequest", nlohmann::json{{"action", "list-books"}}, "Processing ListBooks...");
        } else {
            std::cerr << "Unknown action: " << action << std::endl;
        }
    }

    void consumeQueue(const std::string &queueName, const RabbitMQAdapter::MessageCallback &callback) {
        RabbitMQAdapter::getInstance().consume(queueName, callback);
    }

    void listenForMicroservice(const std::string& queueName, std::function<void(const nlohmann::json&, uint64_t)> callback) {
        consumeQueue(queueName, [callback](const std::string_view &body, uint64_t deliveryTag, bool redelivered) {
            try {
                std::string messageStr(body.data(), body.size());
                auto jsonMessage = nlohmann::json::parse(messageStr);

                if (jsonMessage.contains("action")) {
                    callback(jsonMessage, deliveryTag);
                } else {
                    std::cerr << "Invalid message: missing 'action' key." << std::endl;
                }
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        });
    }

    void sendToMicroservice(const std::string &queueName, const std::string &message) {
        RabbitMQAdapter::getInstance().sendMessage(queueName, message);
    }

    void sendToApiGateway(const std::string &queueName, const std::string &message) {
        RabbitMQAdapter::getInstance().sendMessage(queueName, message);
    }

private:
    void processAction(const std::string &queueName, const nlohmann::json &payload, const std::string &logMessage) {
        std::cout << logMessage << std::endl;
        sendToMicroservice(queueName, payload.dump());
    }
};

#endif // CONNECTOR_HPP
