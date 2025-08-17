//
// Created by bender on 06/08/2025.
//

#include <iostream>

#include "ChatServer.hpp"



int main()
{
    ChatServer server("4566");

    server.Addadmin("itai");

    server.Start();
}