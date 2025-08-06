//
// Created by bender on 06/08/2025.
//

#ifndef CHATAPPLICATION_TCPCLIENT_HPP
#define CHATAPPLICATION_TCPCLIENT_HPP


#include <string>

#include "Socket.hpp"

class TCPClient: Socket
{
public:
    explicit TCPClient(int port_,const std::string& ip_ = "127.0.0.1");
    ~TCPClient() = default;

    int Getserversocket() const;
private:
};


#endif //CHATAPPLICATION_TCPCLIENT_HPP