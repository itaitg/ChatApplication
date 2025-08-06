//
// Created by bender on 06/08/2025.
//

#ifndef CHATAPPLICATION_SERVERCOMMANDS_HPP
#define CHATAPPLICATION_SERVERCOMMANDS_HPP


#include <atomic>
#include <string>


class Servercommands
{
public:
    Servercommands() = default;
    ~Servercommands() = default;

    static bool Iscommand(const std::string& command_);



private:
};


#endif //CHATAPPLICATION_SERVERCOMMANDS_HPP