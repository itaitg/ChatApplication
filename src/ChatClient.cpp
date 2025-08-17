//
// Created by bender on 06/08/2025.
//


#include <unistd.h>
#include <stdexcept>
#include <iostream>

#include "ChatClient.hpp"



Chatclient::Chatclient(const char* port_,const char* ip_):
            TCP_Connect(port_, ip_), m_running(true), m_commands(&m_running)
{


    m_fds.push_back({Getfd(), POLLIN, 0});
    m_fds.push_back({STDIN_FILENO, POLLIN, 0});

    while(m_running)
    {
        int ready = poll(m_fds.data(), m_fds.size(), -1);
        if (ready == -1)
        {
            throw std::runtime_error("error: poll");
        }

        if(m_fds[1].revents & POLLIN) //Send
        {
            std::string userinput;

            std::getline(std::cin, userinput);
            send(Getfd(), userinput.c_str(), userinput.size(), 0);

            m_fds[1].revents = POLLOUT;
        }

        if(m_fds[0].revents & POLLIN) // receive
        {
            std::string buffer(4096, '\0');
            ssize_t bytes = recv(Getfd(), buffer.data(), buffer.size(), 0);

            buffer.resize(bytes);

            if(buffer.rfind('/', 0) == 0)
            {
                m_commands.Execute(buffer, 0);
            }
            else
            {
                std::cout << std::string(buffer.data(), 0, bytes) << std::endl;
            }

            m_fds[0].revents = POLLOUT;
        }
    }
}




