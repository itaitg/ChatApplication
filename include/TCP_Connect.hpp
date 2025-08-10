//
// Created by bender on 2/23/25.
//

#ifndef CHAT_APPLICATION_TCP_CONNECT_HPP
#define CHAT_APPLICATION_TCP_CONNECT_HPP


#include "Socket.hpp"


class TCP_Connect : public Socket
{
public:
    TCP_Connect(const char* port_, const char* ip_);
    ~TCP_Connect();

};



#endif //CHAT_APPLICATION_TCP_CONNECT_HPP
