cmake_minimum_required(VERSION 3.20)


add_library(socket_static STATIC Socket.cpp)

add_library(Usercommands_static STATIC Usercommands.cpp)

add_library(Servercommands_static STATIC Servercommands.cpp)

add_library(TCPConnect_static STATIC TCP_Connect.cpp)
target_link_libraries(TCPConnect_static socket_static)

add_library(TCPListener_static STATIC TCP_Listener.cpp)
target_link_libraries(TCPListener_static TCPConnect_static)

add_library(ChatServer_static STATIC ChatServer.cpp)
target_link_libraries(ChatServer_static TCPListener_static Servercommands_static)

add_library(ChatClient_static STATIC ChatClient.cpp)
target_link_libraries(ChatClient_static TCPConnect_static)

add_library(Communicate_Static Communicate.cpp)
target_link_libraries(ChatClient_static Usercommands_static)
