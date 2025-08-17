//
// Created by bender on 06/08/2025.
//

#ifndef CHATAPPLICATION_TCPSERVER_HPP
#define CHATAPPLICATION_TCPSERVER_HPP


#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <poll.h>

#include "Servercommands.hpp"
#include "TCP_Listener.hpp"

class ChatServer: public TCP_Listener
{
public:
    explicit ChatServer(const char* port_);
    ~ChatServer();

    void Start();
    void Addadmin(const std::string& username_);
    void Removeadmin(const std::string& username_);
    std::unordered_map<int, const std::string>* Getclientlist();
private:
    std::unordered_map<int, const std::string> m_clients;
    std::vector<pollfd> m_fds;
    std::vector<int> m_toremove;

    std::unordered_set<std::string> m_admins;
    std::mutex m_safeclients;

    std::atomic<bool> m_running;


    Servercommands m_server_commands;



    bool HandleClient(int fd_);
    void Acceptnewuser();
    void Broadcast(const std::string& message_, int senderfd_);
    void Sendprivate(int fd_, std::string message_);

    std::unordered_set<std::string>* Getadminlist();
    std::vector<int>* Getremovelist();

};


#endif //CHATAPPLICATION_TCPSERVER_HPP