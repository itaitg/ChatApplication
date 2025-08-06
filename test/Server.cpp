//
// Created by bender on 06/08/2025.
//

#include <iostream>

#include "TcpServer.hpp"
#include "Communicate.hpp"


int main()
{
    TCPServer server(6667);

    server.Accept();

    Communicate talk(server.Getclientsocket(), Server);

    int counter = 3;

    while(counter)
    {
        talk.Receive();
        std::string buffer;
        std::getline(std::cin, buffer);
        talk.Send(buffer);
        --counter;
    }

}