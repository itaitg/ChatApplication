//
// Created by bender on 06/08/2025.
//

#ifndef CHATAPPLICATION_TCPCLIENT_HPP
#define CHATAPPLICATION_TCPCLIENT_HPP





#include "TCP_Connect.hpp"
#include "Communicate.hpp"

class Chatclient: public TCP_Connect
{
public:
    explicit Chatclient(const char* port_, const char* ip_ = "127.0.0.1");
    ~Chatclient() = default;

private:
    Communicate m_talk;

};


#endif //CHATAPPLICATION_TCPCLIENT_HPP