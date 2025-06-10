#include "User.hpp"
#include <iostream>

bool login(const std::string &role)
{
    std::string user, pass;
    std::cout << "Username: ";
    std::cin >> user;
    std::cout << "Password: ";
    std::cin >> pass;
    return (role == "admin" && user == "admin" && pass == "1234");
}

bool registerOrLoginUser()
{
    std::string user, pass;
    std::cout << "Enter your name: ";
    std::cin >> user;
    std::cout << "Enter password: ";
    std::cin >> pass;
    // You can write to a file to store user credentials if needed
    return true; // mock success
}
