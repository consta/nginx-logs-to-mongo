cmake_minimum_required(VERSION 3.5)
project(nginx_logs_to_mongo)

set(CMAKE_CXX_STANDARD 14)

add_executable(nginx_logs_to_mongo main.cpp)

find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})

target_link_libraries(nginx_logs_to_mongo PRIVATE mongo::bsoncxx_shared)
target_link_libraries(nginx_logs_to_mongo PRIVATE mongo::mongocxx_shared)

find_package(Catch2 REQUIRED)
add_executable(tests tests.cpp)
target_link_libraries(tests Catch2::Catch2)