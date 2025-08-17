//
// Created by bender on 06/08/2025.
//

#include <netinet/in.h>
#include <stdexcept>
#include <thread>
#include <unistd.h>
#include <atomic>

#include "ChatServer.hpp"


ChatServer::ChatServer(const char* port_) : TCP_Listener(port_),m_running(true),
            m_server_commands(&m_running, Getclientlist(), Getadminlist(), Getremovelist())
{
    m_fds.push_back({Getfd(), POLLIN, 0});
    m_fds.push_back({STDIN_FILENO, POLLIN, 0});
}

ChatServer::~ChatServer()
{
    for(const auto& [fd, name] : m_clients)
    {
        m_toremove.emplace_back(fd);
    }

    for(const auto& fd : m_toremove)
    {
        send(fd, "/quit", 5, 0);
        close(fd);
        m_clients.erase(fd);
        for(auto iter = m_fds.begin(); iter < m_fds.end(); ++iter)
        {
            if(iter->fd == fd)
            {
                m_fds.erase(iter);
                break;
            }
        }
    }
}


void ChatServer::Start()
{
    while (m_running)
    {
        int ready = poll(m_fds.data(), m_fds.size(), -1);
        if (ready == -1)
        {
            throw std::runtime_error("error: poll");
        }

        if(m_fds[1].revents & POLLIN) //from STDIN
        {
            char buffer[4096];

            int bytes = read(STDIN_FILENO, buffer,sizeof(buffer));

            std::string message(buffer);
            message.resize(bytes - 1);

            if(message.rfind('/', 0) == 0)
            {
                m_server_commands.Execute(message, 0);
            }
                m_fds[1].revents = POLLOUT;
        }

        // Check for new connections
        if(m_fds[0].revents & POLLIN)
        {
            Acceptnewuser();
            m_fds[0].revents = POLLOUT;
        }

        // Check client sockets

        for(int i = 2; i < m_fds.size(); ++i)
        {
            if(m_fds[i].revents & POLLIN)
            {
                if(!HandleClient(m_fds[i].fd))
                {
                    m_clients.erase(m_fds[i].fd);
                    m_fds.erase(m_fds.begin() + i);
                }
            }
        }
        for(const auto& fd : m_toremove)
        {
            m_clients.erase(fd);
            for(auto iter = m_fds.begin(); iter < m_fds.end(); ++iter)
            {
                if(iter->fd == fd)
                {
                    m_fds.erase(iter);
                    break;
                }
            }
        }
        m_toremove.clear();
    }
}



void ChatServer::Addadmin(const std::string& username_)
{
    m_admins.emplace(username_);
}

void ChatServer::Removeadmin(const std::string& username_)
{
    for(const auto& name : m_admins)
    {
        if(username_ == name)
        {
            m_admins.erase(name);
        }
    }
}

std::unordered_map<int, const std::string>* ChatServer::Getclientlist()
{
    return &m_clients;
}


bool ChatServer::HandleClient(int fd_)
{
    char buffer[4096];
    int bytes = recv(fd_, buffer, sizeof(buffer) - 1, 0);

    if (bytes <= 0)
    {
        // Client disconnected
        Broadcast(m_clients[fd_] + " left the chat", fd_);
        close(fd_);

        return false;
    }

    buffer[bytes] = '\0';
    std::string message(buffer);

    // Command handling
    if(message.rfind('/', 0) == 0)
    {
         //change to client commands
        if(!m_server_commands.Execute(message, fd_))
        {
            send(fd_, "command doesn't exist\ntype /help for  help", 46, 0);
        }
        return true;
    }

    Broadcast(m_clients[fd_] + ": " + message, fd_);
    return true;

}


void ChatServer::Acceptnewuser()
{

    int newfd = accept(Getfd(), nullptr, nullptr);

    // Add to poll list
    m_fds.push_back({newfd ,POLLIN, 0});

    // Receive username (first message)
    send(newfd ,"enter username", 14, 0);

    char username[256];
    int bytes = recv(newfd, username, sizeof(username), 0);
    if (bytes <= 0)
    {
        close(newfd);
        return;
    }
    username[bytes] = '\0';
    m_clients.emplace(newfd, username);


    Broadcast(username + std::string(" joined the chat"), newfd);
}


void ChatServer::Broadcast(const std::string& message_, int senderfd_)
{
    std::lock_guard lock(m_safeclients);

    for(const auto& [fd, username] : m_clients)
    {
        if (fd != senderfd_) // Don't echo back to sender
        {
            send(fd, message_.data(), message_.size(), 0);
        }
    }
}

void ChatServer::Sendprivate(int fd_, std::string message_)
{
    send(fd_, message_.data(), message_.size(), 0);
}

std::unordered_set<std::string>* ChatServer::Getadminlist()
{
    return &m_admins;
}

std::vector<int>* ChatServer::Getremovelist()
{
    return &m_toremove;
}



