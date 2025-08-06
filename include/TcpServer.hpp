//
// Created by bender on 06/08/2025.
//

#ifndef CHATAPPLICATION_TCPSERVER_HPP
#define CHATAPPLICATION_TCPSERVER_HPP



#include <netinet/in.h>

#include "Socket.hpp"

class TCPServer: public Socket
{
public:
    explicit TCPServer(int port_);
    ~TCPServer();

    void Accept();
    int Getclientsocket() const;
private:
    sockaddr_in m_serveraddress;
    int m_clientsocket;

};


#endif //CHATAPPLICATION_TCPSERVER_HPP