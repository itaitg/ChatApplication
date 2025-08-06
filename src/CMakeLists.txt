cmake_minimum_required(VERSION 3.20)


add_library(socket_static STATIC Socket.cpp)

add_library(TCPServer_static STATIC TcpServer.cpp)
target_link_libraries(TCPServer_static socket_static)

add_library(Communicate_Static Communicate.cpp)

add_library(TCPClient_static STATIC TcpClient.cpp)
target_link_libraries(TCPClient_static socket_static)


