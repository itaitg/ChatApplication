//
// Created by bender on 06/08/2025.
//

#ifndef CHATAPPLICATION_TCPCLIENT_HPP
#define CHATAPPLICATION_TCPCLIENT_HPP


#include <atomic>
#include <vector>
#include <sys/poll.h>

#include "TCP_Connect.hpp"
#include "Clientcommands.hpp"

class Chatclient: public TCP_Connect
{
public:
    explicit Chatclient(const char* port_, const char* ip_ = "127.0.0.1");
    ~Chatclient() = default;

private:
    std::atomic<bool> m_running;
    std::vector<pollfd> m_fds;
    Clientcommands m_commands;

};


#endif //CHATAPPLICATION_TCPCLIENT_HPP