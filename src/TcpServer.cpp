//
// Created by bender on 06/08/2025.
//

#include "TcpServer.hpp"


#include <iostream>
#include <stdexcept>
#include <unistd.h>

TCPServer::TCPServer(const int port_):m_serveraddress(), m_clientsocket()
{
    m_serveraddress.sin_family = AF_INET;
    m_serveraddress.sin_port = htons(port_);
    m_serveraddress.sin_addr.s_addr = INADDR_ANY;


    if(-1 == bind(Getsocket(), reinterpret_cast<sockaddr*>(&m_serveraddress),
        sizeof(m_serveraddress)))
    {
        throw std::runtime_error("error: bind");
    }
    listen(Getsocket(), 5);
}

TCPServer::~TCPServer()
{
    close(m_clientsocket);
}

void TCPServer::Accept()
{
    sockaddr_in clientAddress{};
    socklen_t clientSize = sizeof(clientAddress);
    m_clientsocket = accept(Getsocket(), reinterpret_cast<sockaddr*>(&clientAddress),
        &clientSize);
}

int TCPServer::Getclientsocket() const
{
    return m_clientsocket;
}


