//
// Created by bender on 06/08/2025.
//

#ifndef CHATAPPLICATION_TCPCLIENT_HPP
#define CHATAPPLICATION_TCPCLIENT_HPP



#include <string>

#include "Socket.hpp"

class Chatclient: Socket
{
public:
    explicit Chatclient(int port_,const std::string& ip_ = "127.0.0.1");
    ~Chatclient() = default;

    int Getserversocket() const;
private:

};


#endif //CHATAPPLICATION_TCPCLIENT_HPP