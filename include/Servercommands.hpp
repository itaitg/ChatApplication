//
// Created by bender on 06/08/2025.
//

#ifndef CHATAPPLICATION_SERVERCOMMANDS_HPP
#define CHATAPPLICATION_SERVERCOMMANDS_HPP


#include <atomic>
#include <unordered_set>

#include "Commands.hpp"


class Servercommands : public Commands
{
public:
    Servercommands(std::atomic<bool>* running_, std::unordered_map<int, const std::string>* clients_
        , std::unordered_set<std::string>* admins_, std::vector<int>* remove_list_ );

    void HandleQuit(const int& fd_);
    void HandleKick(const std::string& username);
    void HandleHelp(const int& fd_);
    void Handleprivate(const std::string& message_, const int& fd_);

private:
    std::atomic<bool>* m_running;
    std::unordered_map<int, const std::string>* m_clients;
    std::vector<int>* m_toremove;
    std::unordered_set<std::string>* m_admins;

    bool Isadmin(const std::string& username_);
};


#endif //CHATAPPLICATION_SERVERCOMMANDS_HPP