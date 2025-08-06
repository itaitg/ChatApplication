//
// Created by bender on 06/08/2025.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "ChatClient.hpp"

#include <stdexcept>

TCPClient::TCPClient(const int port_,const std::string& ip_)
{
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port_);
    inet_pton(AF_INET, ip_.c_str(), &serverAddress.sin_addr);
    if(-1 == connect(Getsocket(), reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)))
    {
        throw std::runtime_error("error: can't connect to server");
    }
}

int TCPClient::Getserversocket() const
{
    return Getsocket();
}


