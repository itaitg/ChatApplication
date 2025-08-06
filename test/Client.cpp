//
// Created by bender on 06/08/2025.
//

#include <iostream>

#include "TcpClient.hpp"
#include "Communicate.hpp"


int main()
{
    TCPClient client(6667);
    Communicate talk(client.Getserversocket(), Client);

    int counter = 3;

    while(counter)
    {
        std::string buffer;
        std::getline(std::cin, buffer);
        talk.Send(buffer);
        talk.Receive();
        --counter;
    }

    return 0;
}