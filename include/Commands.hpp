//
// Created by bender on 06/08/2025.
//

#ifndef CHATAPPLICATION_COMMANDS_HPP
#define CHATAPPLICATION_COMMANDS_HPP

#include <functional>
#include <unordered_map>
#include <string>

class Commands
{
public:
    void RegisterCommand(const std::string& cmd_,
                std::function<void(const std::string&, const int&)> handler_);

    bool Execute(const std::string& input_, const int& fd_);

protected:
    std::unordered_map<std::string, std::function
                <void(const std::string&, const int&)>> m_commands;
};


#endif //CHATAPPLICATION_COMMANDS_HPP