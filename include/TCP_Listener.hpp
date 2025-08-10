//
// Created by bender on 2/22/25.
//


#ifndef CHAT_APPLICATION_TCP_SERVER_HPP
#define CHAT_APPLICATION_TCP_SERVER_HPP

#include <string>
#include <vector>

#include "Socket.hpp"


class TCP_Listener : public Socket
{
public:
    explicit TCP_Listener(const char* port_);
    ~TCP_Listener() = default;
private:

};


#endif //ILRD_RD329_TCP_SERVER_HPP
