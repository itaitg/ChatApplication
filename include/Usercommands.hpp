//
// Created by bender on 06/08/2025.
//

#ifndef CHATAPPLICATION_USERCOMMANDS_HPP
#define CHATAPPLICATION_USERCOMMANDS_HPP

#include <atomic>
#include <string>



class Usercommands
{
public:
    Usercommands() = default;;
    ~Usercommands() = default;

    void Commandcheck(const std::string& input_, std::atomic<bool>* running_);

private:

};


#endif //CHATAPPLICATION_USERCOMMANDS_HPP