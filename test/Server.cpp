//
// Created by bender on 06/08/2025.
//

#include <iostream>

#include "ChatServer.hpp"



int main()
{
    ChatServer server(6667);

    server.Start();

}