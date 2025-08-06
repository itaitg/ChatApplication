//
// Created by bender on 06/08/2025.
//

#include <netinet/in.h>
#include <stdexcept>
#include <thread>
#include <unistd.h>

#include "ChatServer.hpp"

ChatServer::ChatServer(const int port_): m_max_clients(5)
{
    sockaddr_in m_serveraddress{};
    m_serveraddress.sin_family = AF_INET;
    m_serveraddress.sin_port = htons(port_);
    m_serveraddress.sin_addr.s_addr = INADDR_ANY;

    int y = 1;

    setsockopt(Getsocket(), SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int));

    if(-1 == bind(Getsocket(), reinterpret_cast<sockaddr*>(&m_serveraddress),
        sizeof(m_serveraddress)))
    {
        throw std::runtime_error("error: bind");
    }
    listen(Getsocket(), m_max_clients);
}



void ChatServer::Start()
{
    while(true)
    {
        sockaddr_in clientAddress{};
        socklen_t clientSize = sizeof(clientAddress);
        int clientfd = accept(Getsocket(), reinterpret_cast<sockaddr*>(&clientAddress),
            &clientSize);

        std::thread(&ChatServer::Handleclient, this, clientfd).detach();
    }
}

void ChatServer::Handleclient(const int clientfd_)
{
    //Get username (first message)
    std::string username(256, '\0');
    const std::string buffer = {"enter username"};

    send(clientfd_ ,buffer.c_str(), buffer.size() + 1, 0);
    int bytes = recv(clientfd_, username.data() , sizeof(username), 0);
    if (bytes <= 0)
    {
        close(clientfd_);
        return;
    }
    username[bytes] = '\0';

    {
        std::lock_guard lock(m_safeclients);
        m_clients.emplace(std::pair(clientfd_, username.data()));
    }

    Broadcast(username.c_str() + std::string(" joined the chat"), clientfd_);

    while(true)
    {
        char buffer[4096];
        bytes = recv(clientfd_, buffer, sizeof(buffer), 0);

        if (bytes <= 0)
        {
            break; // Client disconnected
        }
        buffer[bytes] = '\0';
        std::string message = m_clients[clientfd_] + ": " + buffer;
        Broadcast(message, clientfd_);
    }

    {
        std::lock_guard lock(m_safeclients);
        m_clients.erase(clientfd_);
    }
    Broadcast(username.c_str() + std::string(" left the chat"), clientfd_);
    close(clientfd_);

}


void ChatServer::Broadcast(const std::string& message_, int senderfd_)
{
    std::lock_guard lock(m_safeclients);

    for(const auto& [fd, username] : m_clients)
    {
        if (fd != senderfd_) // Don't echo back to sender
        {
            send(fd, message_.c_str(), message_.size(), 0);
        }
    }
}



