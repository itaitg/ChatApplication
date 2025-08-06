//
// Created by bender on 06/08/2025.
//

#ifndef CHATAPPLICATION_TCPSERVER_HPP
#define CHATAPPLICATION_TCPSERVER_HPP


#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "Servercommands.hpp"
#include "Socket.hpp"

class ChatServer: public Socket
{
public:
    explicit ChatServer(int port_);
    ~ChatServer() = default;

    void Start();
    void Addadmin(const std::string& username_);
private:
    std::unordered_map<int, std::string> m_clients;
    std::vector<std::string> m_admins;
    std::mutex m_safeclients;
    int m_max_clients;

    Servercommands commands;
    void Handleclient(int clientfd_);
    void Broadcast(const std::string& message_, int senderfd_);

};


#endif //CHATAPPLICATION_TCPSERVER_HPP