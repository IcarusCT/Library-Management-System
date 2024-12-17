cmake_minimum_required(VERSION 3.30)
project(user-management)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        ${PROJECT_NAME}
        application/user-management-service.hpp
        domain/user.hpp
        domain/user-factory.hpp
        domain/user-service.hpp
        domain/user-repository.hpp
        main.cpp
        user-dto/user-dto-assembler.hpp


)

target_link_libraries(user-management PRIVATE ${COMMON_LIBRARIES})