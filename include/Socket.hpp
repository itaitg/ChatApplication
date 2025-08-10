//
// Created by bender on 06/08/2025.
//

#ifndef CHAT_APPLICATION_SOCKET_HPP
#define CHAT_APPLICATION_SOCKET_HPP

#include <netdb.h>

class Socket
{
public:
    Socket(const char* port_, const char* ip_);
    ~Socket();
    int Getfd() const;
    sockaddr* GetAddr() const;
private:
    int m_fd;
    addrinfo* m_res;
};


#endif //CHAT_APPLICATION_SOCKET_HPP