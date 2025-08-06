//
// Created by bender on 06/08/2025.
//

#ifndef CHATAPPLICATION_COMMUNICATE_HPP
#define CHATAPPLICATION_COMMUNICATE_HPP
#include <string>

enum Status
{
    Client,
    Server
};


class Communicate
{
public:
    explicit Communicate(int other_fd_, Status status_);
    ~Communicate() = default;


    void Receive() const;
    void Send(const std::string& message_) const;
private:
    int m_fd;
    std::string m_buddy;
};


#endif //CHATAPPLICATION_COMMUNICATE_HPP