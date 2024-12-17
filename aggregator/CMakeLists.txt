cmake_minimum_required(VERSION 3.30)
project(aggregator)

set(CMAKE_CXX_STANDARD 20)

find_package(Crow CONFIG REQUIRED)
find_package(amqpcpp REQUIRED)
find_package(Boost REQUIRED)

add_executable( ${PROJECT_NAME}
        main.cpp
        ms-router.hpp
        connector.hpp
)

include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${CMAKE_SOURCE_DIR}/api-gateway)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Crow::Crow
        amqpcpp
)