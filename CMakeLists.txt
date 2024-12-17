cmake_minimum_required(VERSION 3.30)
project(LibraryManagementSystem)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/libs)


add_subdirectory(
        book-management
)
add_subdirectory(
        user-management
)
add_subdirectory(
        aggregator
)
add_subdirectory(
        api-gateway
)

