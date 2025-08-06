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
            std::cout << "Commands:\n"
                      << "/quit - Exit chat\n"
                      << "/help - Show this help\n";
        }
        else
        {
            std::cout << "Unknown command. Type /help for options.\n";
        }
    }
}
