//
// Created by bender on 06/08/2025.
//



#include <iostream>
#include <netinet/in.h>

#include "Communicate.hpp"

Communicate::Communicate(const int other_fd_, Status status_): m_fd(other_fd_)
{
    if(status_ == Client)
    {
        m_buddy = "Server: ";
    }
    else
    {
        m_buddy = "Client: ";
    }
}

void Communicate::Receive() const
{
    char buffer[1024] = {};
    int bytesReceived = recv(m_fd, buffer, 1024, 0);
    if (bytesReceived == -1)
    {
        std::cerr << "Error receiving message!" << std::endl;
        return;
    }
    if (bytesReceived == 0)
    {
        std::cout << "Client disconnected." << std::endl;
        return;
    }
    std::cout << m_buddy << std::string(buffer, 0, bytesReceived) << std::endl;
}

void Communicate::Send(const std::string& message_) const
{
    send(m_fd ,message_.c_str(), message_.size() + 1, 0);
}