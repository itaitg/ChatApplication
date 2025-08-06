//
// Created by bender on 06/08/2025.
//

#ifndef CHAT_APPLICATION_SOCKET_HPP
#define CHAT_APPLICATION_SOCKET_HPP

class Socket
{
public:
    Socket();
    ~Socket();
    int Getsocket() const;
private:
    int m_socket;

    static int Init();
};


#endif //CHAT_APPLICATION_SOCKET_HPP