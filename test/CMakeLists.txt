cmake_minimum_required(VERSION 3.20)


project(server)
add_executable(server Server.cpp)
target_link_libraries(server TCPServer_static Communicate_Static)

project(client)
add_executable(client Client.cpp)
target_link_libraries(client TCPClient_static Communicate_Static)