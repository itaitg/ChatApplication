cmake_minimum_required(VERSION 3.20)


project(server)
add_executable(server Server.cpp)
target_link_libraries(server ChatServer_static)

project(client)
add_executable(client Client.cpp)
target_link_libraries(client ChatClient_static)