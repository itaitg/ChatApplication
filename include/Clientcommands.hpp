//
// Created by bender on 11/08/2025.
//

#ifndef CHATAPPLICATION_CLIENTCOMMANDS_HPP
#define CHATAPPLICATION_CLIENTCOMMANDS_HPP

#include <atomic>

#include "Commands.hpp"

class Clientcommands: public Commands
{
public:
    Clientcommands(std::atomic<bool>* running_);

    void HandleQuit();

private:
    std::atomic<bool>* m_running;
};


#endif //CHATAPPLICATION_CLIENTCOMMANDS_HPP