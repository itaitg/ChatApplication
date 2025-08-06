//
// Created by bender on 06/08/2025.
//

#include <iostream>

#include "ChatClient.hpp"
#include "Communicate.hpp"


int main()
{
    Chatclient client(5666);
    Communicate talk(client.Getserversocket());


    talk.Send();


    return 0;
}