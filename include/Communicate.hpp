//
// Created by bender on 06/08/2025.
//

#ifndef CHATAPPLICATION_COMMUNICATE_HPP
#define CHATAPPLICATION_COMMUNICATE_HPP


#include <atomic>
#include <string>
#include <thread>

#include "Usercommands.hpp"

class Communicate
{
public:
    explicit Communicate(int other_fd_);
    ~Communicate();

    void Send();
private:
    int m_fd;
    std::string m_buddy;
    std::atomic<bool> m_running;
    std::thread m_receivethread;
    Usercommands m_commands;

    void Receivemessages();
};


#endif //CHATAPPLICATION_COMMUNICATE_HPP