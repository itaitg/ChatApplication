//
// Created by bender on 06/08/2025.
//

#include <iostream>

#include "Usercommands.hpp"



void Usercommands::Commandcheck(const std::string& input_, std::atomic<bool>* running_)
{
    if (input_.rfind('/', 0) == 0) // Check if input starts with /
    {
        if (input_ == "/quit")
        {
            *running_ = false;
        }
        else if (input_ == "/help")
        {
            std::cout << "Commands:" << std::endl;
            std::cout << "/quit - Exit chat" << std::endl;
            std::cout << "/help - Show this help" << std::endl;
            std::cout << "ADMIN ONLY" << std::endl;
            std::cout << "/kick <name> - Kick user from server" << std::endl;

        }
        else
        {
            std::cout << "Unknown command. Type /help for options.\n";
        }
    }
}
