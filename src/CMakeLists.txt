cmake_minimum_required(VERSION 3.20)


add_library(socket_static STATIC Socket.cpp)

add_library(Usercommands_static STATIC Usercommands.cpp)

add_library(Servercommands_static STATIC Servercommands.cpp)

add_library(ChatServer_static STATIC ChatServer.cpp)
target_link_libraries(ChatServer_static socket_static Servercommands_static)

add_library(ChatClient_static STATIC ChatClient.cpp)
target_link_libraries(ChatClient_static socket_static)

add_library(Communicate_Static Communicate.cpp)
target_link_libraries(ChatClient_static Usercommands_static)
