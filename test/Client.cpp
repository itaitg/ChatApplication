//
// Created by bender on 06/08/2025.
//

#include <iostream>

#include "ChatClient.hpp"
#include "Communicate.hpp"


int main()
{
    TCPClient client(6667);
    Communicate talk(client.Getserversocket());

    int counter = 3;

    while(counter)
    {
        talk.Receive();
        std::string buffer;
        std::getline(std::cin, buffer);
        talk.Send(buffer);
        --counter;
    }

    return 0;
}