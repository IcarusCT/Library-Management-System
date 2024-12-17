cmake_minimum_required(VERSION 3.30)
project(api-gateway)

set(CMAKE_CXX_STANDARD 20)

find_package(Crow CONFIG REQUIRED)
find_package(amqpcpp REQUIRED)
find_package(Boost REQUIRED)

add_executable( ${PROJECT_NAME}
        gateway.hpp
        main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Crow::Crow
        amqpcpp
)