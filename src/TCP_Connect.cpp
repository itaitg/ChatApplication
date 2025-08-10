//
// Created by bender on 2/23/25.
//

#include "TCP_Connect.hpp"

#include <stdexcept>
#include <sys/socket.h>


TCP_Connect::TCP_Connect(const char* port_, const char* ip_):
                        Socket(port_, ip_)
{
    if(-1 == connect(Getfd(), GetAddr(), sizeof(*GetAddr())))
    {
        throw std::runtime_error("error: connect");
    }
}

TCP_Connect::~TCP_Connect()
{

}

