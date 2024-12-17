cmake_minimum_required(VERSION 3.30)
project(book-management)

set(CMAKE_CXX_STANDARD 20)

find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(
        ${PROJECT_NAME}
        main.cpp
        application/book-management-service.hpp
        domain/book-factory.hpp
        domain/book-service.hpp
        domain/book-repository.hpp
        domain/book.hpp
        library-dto/library-dto-assembler.hpp
        library-dto/request/add-book-request.hpp
        library-dto/response/get-all-books-response.hpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        nlohmann_json::nlohmann_json
        mongo::bsoncxx_static
        mongo::mongocxx_static
        amqpcpp

)
