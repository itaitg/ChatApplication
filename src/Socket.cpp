//
// Created by bender on 06/08/2025.
//

#include <sys/socket.h>
#include <unistd.h>

#include "Socket.hpp"


Socket::Socket(): m_socket(Init())
{}

Socket::~Socket()
{
    close(m_socket);
}

int Socket::Getsocket() const
{
    return m_socket;
}

int Socket::Init()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}
