#ifndef GATEWAY_HPP
#define GATEWAY_HPP
#include <crow.h>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../libs/libcpp-event-hub.hpp"
#include "../libs/rabbit-mq-adapter.hpp"
using namespace lklibs;

class Gateway {
public:
    Gateway() : rabbitMQ(RabbitMQAdapter::getInstance()) {
        setupRoutes();
    }

    crow::SimpleApp app;
    RabbitMQAdapter &rabbitMQ;

    void setupRoutes() {
        CROW_ROUTE(app, "/").methods(crow::HTTPMethod::POST)(
            [this](const crow::request &req, crow::response &res) {
                try {
                    const auto it = req.headers.find("action");

                    const auto action = it->second;
                    const auto payload = !req.body.empty() ? req.body : "{}";
                    nlohmann::json jsonMessage;
                                jsonMessage["action"] = action;
                                jsonMessage["payload"] = nlohmann::json::parse(payload);
                    std::string message = jsonMessage.dump();
                    rabbitMQ.sendMessage("api_requests", message);

                    res.code = 200;
                    res.write("Message forwarded to aggregator.");
                } catch (const std::exception &e) {
                    res.code = 500;
                    res.write(std::string("Error: ") + e.what());
                }
                res.end();
            });
    }

    void startThreads() {
        rabbitMQ.init("amqp://guest:guest@localhost/");
        std::cout << "Starting API Gateway..." << std::endl;

        std::thread rabbitThread([this]() {
            listenToAggregatorResponses();
        });

        std::thread rabbitStartThread([this]() {
            rabbitMQ.start();
        });

        std::thread crowServerThread([this]() {
            app.port(8080).multithreaded().run();
        });
        rabbitThread.join();
        rabbitStartThread.join();
        crowServerThread.join();
    }

    void listenToAggregatorResponses() {
        auto &eventHub = EventHub::getInstance();

        rabbitMQ.consume("aggregator_queue", [&](const std::string_view &body, uint64_t deliveryTag, bool redelivered) {
            std::cout << "Message received: " << body << std::endl;
            eventHub.emit("message_received", "Aggregator", std::string(body));

            rabbitMQ.ack(deliveryTag);
        });
    }
};
#endif // GATEWAY_HPP
