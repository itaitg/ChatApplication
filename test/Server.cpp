//
// Created by bender on 06/08/2025.
//

#include <iostream>

#include "ChatServer.hpp"



int main()
{
    ChatServer server(5666);

    server.Addadmin("itai");

    server.Start();
}