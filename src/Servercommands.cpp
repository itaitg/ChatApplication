//
// Created by bender on 06/08/2025.
//

#include "Servercommands.hpp"

#include <unistd.h>
#include <sys/socket.h>


Servercommands::Servercommands(std::atomic<bool>* running_,
                std::unordered_map<int, const std::string>* clients_,
                std::unordered_set<std::string>* admins_, std::vector<int>* remove_list_ ):
                m_running(running_), m_clients(clients_), m_admins(admins_), m_toremove(remove_list_)
{

    RegisterCommand("close", [this](const auto&, const int&) { *m_running = false; });
    RegisterCommand("quit", [this](const auto&, const int& fd_) { this->HandleQuit(fd_); });
    RegisterCommand("kick", [this](const std::string& args, const int&) { this->HandleKick(args);});
    RegisterCommand("help", [this](const auto&, const int& fd_) { this->HandleHelp(fd_); });
    RegisterCommand("private", [this](const std::string& args, const int& fd_) { this->Handleprivate(args, fd_);});
}

void Servercommands::HandleQuit(const int& fd_)
{
    send(fd_, "/quit", 5, 0);
    close(fd_);
    m_toremove->emplace_back(fd_);

}

void Servercommands::HandleKick(const std::string& username)
{
    for (auto& [fd, name] : *m_clients)
    {
        if (name == username)
        {
            //send(fd, "You were kicked by admin!", 25, 0);
            send(fd, "/quit", 5, 0);
            close(fd);
            m_toremove->emplace_back(fd);
            break;
        }
    }
}

void Servercommands::HandleHelp(const int& fd_)
{
    std::string helpmessage("Available commands:\n"
                "/quit - Disconnect from server\n"
                "/help - Show this message\n"
                "/private <username> <message> - Send private message");

    send(fd_, helpmessage.data(), helpmessage.size(), 0);
}

bool Servercommands::Isadmin(const std::string& username_)
{
    for(const auto& admin : *m_admins)
    {
        if(username_ == admin)
        {
            return true;
        }
    }
        return false;
}

void Servercommands::Handleprivate(const std::string& message_, const int& fd_)
{
    size_t spacePos = message_.find(' ');
    if (spacePos == std::string::npos)
    {
        send(fd_, "Usage: /private <username> <message>", 36, 0);
        return;
    }


    std::string sender;

    for (auto& [fd, name] : *m_clients)
    {
        if(fd == fd_)
            sender = name;
    }

    const std::string recipient = message_.substr(0, spacePos);
    const std::string message = "PM from " + sender + ": " + message_.substr(spacePos + 1);


    for (auto& [fd, name] : *m_clients)
    {
        if (name == recipient)
        {
            send(fd, message.data(), message.size(), 0);
            break;
        }
    }
}
