//
// Created by elif on 12/10/24.
//
#include <nlohmann/json.hpp>
#include "../libs/rabbit-mq-adapter.hpp"
#include "application/user-management-service.hpp"
#include "user-dto/request/add-user-request.hpp"

using json = nlohmann::json;

 int main() {
     RabbitMQAdapter &rabbitMQ = RabbitMQAdapter::getInstance();
     rabbitMQ.init("amqp://guest:guest@localhost/");

     rabbitMQ.consume("AddBook", [&](const std::string_view &body, uint64_t deliveryTag, bool redelivered) {
         try {
             std::cout << "[AddBook] Received request: " << body << std::endl;
             auto jsonMessage = nlohmann::json::parse(body);

             AddUserRequest request = jsonMessage.get<AddUserRequest>();
             std::cout << "[AddBook] Adding book: " << request.title << " by " << request.author << std::endl;

             userManagementService.AddUser(request);
             RabbitMQAdapter::getInstance().ack(deliveryTag);
         } catch (const std::exception &e) {
             std::cerr << "[AddBook] Error: " << e.what() << std::endl;
         }
     });
 }