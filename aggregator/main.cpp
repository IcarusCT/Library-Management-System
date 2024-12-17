#include "connector.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

int main() {
    Connector connector;

    connector.getFromApiGateway("api_requests",
    [&](const std::string_view &message, uint64_t deliveryTag, bool redelivered) {
        try {
            std::string messageStr(message.data(), message.size());
            std::cout << "Received request: " << messageStr << std::endl;

            auto jsonMessage = nlohmann::json::parse(messageStr);
            std::string action = jsonMessage.at("action").get<std::string>();
            nlohmann::json payload = jsonMessage.at("payload");

            std::cout << "Action: " << action << std::endl;
            std::cout << "Payload: " << payload.dump() << std::endl;

            connector.handleApiRequest(action, payload);

            RabbitMQAdapter::getInstance().ack(deliveryTag);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    });

    connector.getFromApiGateway("ListBooks",
   [&](const std::string_view &message, uint64_t deliveryTag, bool redelivered) {
       try {
           std::string messageStr(message.data(), message.size());
           std::cout << "Received response from microservice: " << messageStr << std::endl;

           auto jsonMessage = nlohmann::json::parse(messageStr);
            if (jsonMessage.contains("list-response")) {
                std::string listResponse = jsonMessage["list-response"];
                std::cout << "Listing response: " << listResponse << std::endl;
            } else {
                std::cerr << "Error: 'list-response' key not found in response." << std::endl;
            }
           RabbitMQAdapter::getInstance().ack(deliveryTag);
       } catch (const std::exception &e) {
           std::cerr << "Error: " << e.what() << std::endl;
       }
   });

    std::cout << "Aggregator is listening for requests." << std::endl;
    RabbitMQAdapter::getInstance().start();

    return 0;
}
