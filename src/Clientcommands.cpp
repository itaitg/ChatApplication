//
// Created by bender on 11/08/2025.
//

#include "Clientcommands.hpp"

Clientcommands::Clientcommands(std::atomic<bool>* running_): m_running(running_)
{
    RegisterCommand("quit", [this](const auto&, const int&) { this->HandleQuit(); });
}

void Clientcommands::HandleQuit()
{
    *m_running = false;
}
