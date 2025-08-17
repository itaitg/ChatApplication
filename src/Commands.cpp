//
// Created by bender on 06/08/2025.
//


#include "Commands.hpp"


void Commands::RegisterCommand(const std::string& cmd_,
    std::function<void(const std::string&, const int&)> handler_)
{
    m_commands[cmd_] = std::move(handler_);
}

bool Commands::Execute(const std::string& input_, const int& fd_)
{
    size_t spacePos = input_.find(' ');
    std::string cmd = input_.substr(1, spacePos - 1);
    std::string args = (spacePos != std::string::npos) ? input_.substr(spacePos + 1) : "";

    if(m_commands.find(cmd) != m_commands.end())
    {
        m_commands[cmd](args, fd_);
        return true;
    }
    return false;


}
