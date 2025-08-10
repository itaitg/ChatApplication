//
// Created by bender on 06/08/2025.
//

#include <netinet/in.h>
#include <stdexcept>
#include <thread>
#include <unistd.h>
#include <atomic>

#include "ChatServer.hpp"


ChatServer::ChatServer(const char* port_) : TCP_Listener(port_)
{
    m_fds.push_back({Getfd(), POLLIN, 0});
    m_fds.push_back({STDIN_FILENO, POLLIN, 0});
}


void ChatServer::Start()
{
    bool running{true};

    while (running)
    {
        int ready = poll(m_fds.data(), m_fds.size(), -1);
        if (ready == -1)
        {
            throw std::runtime_error("error: poll");
            running = false;
        }

        if(m_fds[1].revents & POLLIN) //from STDIN
        {

        }

        // Check for new connections
        if(m_fds[0].revents & POLLIN)
        {
            Acceptnewuser();
            m_fds[0].revents = POLLOUT;
        }

        // Check client sockets

        for(const auto& event : m_fds)
        {
            if (event.revents & POLLIN)
            {
                HandleClient(event.fd);
            }

        }
        //remove fds loop and clear

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
/*
void ChatServer::Handleclient(const int clientfd_)
{
    //Get username (first message)
    std::string username(256, '\0');
    const std::string buffer = {"enter username"};
    bool name_found = true;
    while(name_found)
    {
        username.resize(256);
        username[25] = '\0';
        send(clientfd_ ,buffer.c_str(), buffer.size(), 0);
        int bytes = recv(clientfd_, username.data() , sizeof(username), 0);
        if (bytes <= 0)
        {
            close(clientfd_);
            return;
        }
        name_found = false;
        username.resize(bytes);
        username[bytes] = '\0';
        for(const auto& [fd, name]: m_clients) //make sure username is unique
        {
            if(name == username)
            {
                const std::string pick_again = "username take, please pick again.";
                name_found = true;
                send(clientfd_ ,pick_again.c_str(), pick_again.size() + 1, 0);
            }
        }
    }

        {
            std::lock_guard lock(m_safeclients);
            m_clients.emplace(std::pair(clientfd_, username.data()));
        }
    Broadcast(username.c_str() + std::string(" joined the chat"), clientfd_);

    std::atomic<bool> running{true};

    while(running)
    {
        std::string from(4096, '\0');
        int bytes = recv(clientfd_, from.data(), from.size(), 0);

        if(bytes <= 0)
        {
            break; // Client disconnected
        }

        if(!Servercommands::Iscommand(from))
        {
            from[bytes] = '\0';
            std::string message = m_clients[clientfd_] + ": " + from;
            Broadcast(message, clientfd_);
        }
        else // handle commands
        {
            if(from.substr(0, 5) == "/kick")
            {
                bool admin = false;
                // Admin check
                for( const auto& name : m_admins)
                {
                    if(m_clients[clientfd_] == name)
                    {
                        std::string target = from.substr(6);
                        target.resize(target.length());
                        Kickuser(target);
                    }
                    else
                    {
                        Sendprivate(clientfd_, "Error: Admin-only command");
                    }
                }
            }
        }
    }

    {
        std::lock_guard lock(m_safeclients);
        m_clients.erase(clientfd_);
    }
    Broadcast(username.c_str() + std::string(" left the chat"), clientfd_);
    close(clientfd_);

}*/

void ChatServer::Kickuser(std::string user_) //not working (can't recognise names)
{
    std::lock_guard lock(m_safeclients);
    for (const auto& [fd, name] : m_clients)
    {
        if (name == user_)
        {
            send(fd, "You were kicked by admin!", 24, 0);
            close(fd);
            m_clients.find(fd);
            m_clients.erase(m_clients.find(fd));
            Broadcast(user_ + " was kicked by admin", -1);
        }
    }
}

void ChatServer::HandleClient(int fd_)
{
    char buffer[4096];
    int bytes = recv(fd_, buffer, sizeof(buffer) - 1, 0);

    if (bytes <= 0)
    {
        // Client disconnected
        Broadcast(m_clients[fd_] + " left the chat", fd_);
        m_clients.erase(fd_);
        //m_toremove.push_back({fd_, 0, 0});
        return;
    }

    buffer[bytes] = '\0';
    std::string message(buffer);

    // Command handling
    // if(message.rfind('/', 0) == 0)
    // {
    //     if (message == "/quit") return false;
    //     if (message.starts_with("/kick ") && m_clients[clientFd] == "admin") {
    //         KickUser(message.substr(6));
    //     }
    // }
    //else // Broadcast normal message
    {
        Broadcast(m_clients[fd_] + ": " + message, fd_);
    }
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
    m_clients[newfd] = username;


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



