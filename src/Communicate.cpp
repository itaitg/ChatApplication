//
// Created by bender on 06/08/2025.
//



#include <iostream>
#include <netinet/in.h>
#include <vector>

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
    std::string buffer(1024, '\0');

    recv(m_fd, buffer.data() , buffer.size(), 0);

    std::cout << m_buddy << std::string(buffer.data(), 0, buffer.size()) << std::endl;
}

void Communicate::Send(const std::string& message_) const
{
    send(m_fd ,message_.c_str(), message_.size() + 1, 0);
}