#include "connector.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

int main() {
    Connector connector;
    connector.consumeQueue("api_requests", [&](const std::string_view &message, uint64_t deliveryTag, bool redelivered) {
        try {
            std::string messageStr(message.data(), message.size());
            auto jsonMessage = nlohmann::json::parse(messageStr);

            std::string action = jsonMessage.at("action").get<std::string>();
            nlohmann::json payload = jsonMessage.at("payload");

            if (action == "list-books") {
                RabbitMQAdapter::getInstance().sendMessage("ListBooksRequest", jsonMessage.dump());
                std::cout << "[Aggregator] Forwarded list-books request to microservice." << std::endl;
            }

            RabbitMQAdapter::getInstance().ack(deliveryTag);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    });

    connector.listenForMicroservice("ListBooksResponse", [&](const nlohmann::json& message, uint64_t deliveryTag) {
        try {
            std::cout << "[Aggregator] Received response from microservice: " << message.dump() << std::endl;

            RabbitMQAdapter::getInstance().sendMessage("aggregator_queue", message.dump());
            std::cout << "[Aggregator] Forwarded response to API Gateway: " << message.dump() << std::endl;

            RabbitMQAdapter::getInstance().ack(deliveryTag);

        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    });

    std::cout << "Aggregator is listening for requests." << std::endl;
    RabbitMQAdapter::getInstance().start();

    return 0;
}
