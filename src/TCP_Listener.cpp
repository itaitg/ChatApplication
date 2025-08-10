//
// Created by bender on 2/22/25.
//

#include "TCP_Listener.hpp"

#include <stdexcept>
#include <unistd.h>

TCP_Listener::TCP_Listener(const char* port_): Socket
                                    (port_, nullptr)
{
    int y = 1;

    if(setsockopt(Getfd(), SOL_SOCKET, SO_REUSEADDR,
                &y , sizeof(int)) == -1)
    {
        throw std::runtime_error("error: setsockopt");
    }

    if(-1 == bind(Getfd(), GetAddr(), sizeof(*GetAddr())))
    {
        throw std::runtime_error("error: bind");
    }
    listen(Getfd(), 10); //magic number temp

}



