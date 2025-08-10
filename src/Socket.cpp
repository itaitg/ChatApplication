//
// Created by bender on 06/08/2025.
//

#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

#include "Socket.hpp"

#include <stdexcept>


Socket::Socket(const char* port, const char* ip_): m_fd(), m_res()
{
    addrinfo hints = {};
    int status = 0;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo(ip_, port, &hints, &m_res);
    if(status)
    {
        throw std::runtime_error("error: getaddrinfo");
    }
    m_fd = socket(m_res->ai_family,m_res->ai_socktype,m_res->ai_protocol);
    if(m_fd == -1)
    {
        throw std::runtime_error("error: socket");
    }
}

Socket::~Socket()
{
    freeaddrinfo(m_res);
    close(m_fd);
}

int Socket::Getfd() const
{
    return m_fd;
}

sockaddr* Socket::GetAddr() const
{
    return m_res->ai_addr;
}
