//
// Created by bender on 06/08/2025.
//



#include <iostream>
#include <netinet/in.h>
#include <vector>

#include <unistd.h>

#include "Communicate.hpp"



Communicate::Communicate(const int other_fd_): m_fd(other_fd_), m_running(true),
                    m_receivethread(&Communicate::Receivemessages, this)
{}

Communicate::~Communicate()
{
    m_running = false;
    m_receivethread.join();
    close(m_fd);
}

void Communicate::Receivemessages()
{
    std::string buffer(4096, '\0');
    while(m_running)
    {
        timeval tv = {2, 0};
        setsockopt(m_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(timeval));

        ssize_t bytes = recv(m_fd, buffer.data(), buffer.size(), 0);

        if(bytes > 0)
        {
            buffer[bytes] = '\0';
            std::cout << std::string(buffer.data(), 0, bytes) << std::endl;
        }
    }
}

void Communicate::Send()
{
    std::string userinput;
    while(m_running)
    {
        std::cout << "> ";
        std::getline(std::cin, userinput);
        m_commands.Commandcheck(userinput, &m_running);
        if (!m_running) break;
        {
            if (send(m_fd, userinput.c_str(), userinput.size(), 0) <= 0)
            {
                std::cerr << "Send failed!" << std::endl;
                m_running = false;
            }
        }
    }
}