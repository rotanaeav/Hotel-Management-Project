#pragma once
#include <string>
#include <vector>
#include "Customer.hpp"

class UserAuth
{
private:
    std::vector<Customer> customers;

public:
    UserAuth();
    bool login(const std::string &username, const std::string &password);
    bool adminLogin(const std::string &username, const std::string &password);
    bool registerUser(const std::string &username, const std::string &password,
                      const std::string &name, const std::string &gender,
                      int age, const std::string &phone);

    void loadUsersFromFile(const std::string &filename);
    void saveUsersToFile(const std::string &filename);
};