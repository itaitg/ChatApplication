//
// Created by bender on 06/08/2025.
//



#include "ChatClient.hpp"

Chatclient::Chatclient(const char* port_,const char* ip_):
            TCP_Connect(port_, ip_), m_talk(Getfd())
{
    m_talk.Send();
}




