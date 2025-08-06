//
// Created by bender on 06/08/2025.
//

#include "Servercommands.hpp"



bool Servercommands::Iscommand(const std::string& command_)
{
    return command_.rfind('/', 0) == 0;
}

bool Servercommands::Isquit(const std::string& command_)

{
    return command_ == "/quit";

}
