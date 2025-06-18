#include "User.hpp"
#include "ExcelUtils.hpp"

UserAuth::UserAuth()
{
    loadUsersFromFile("customers.xlsx");
}

bool UserAuth::login(const std::string &username, const std::string &password)
{
    for (const auto &customer : customers)
    {
        if (customer.getUsername() == username && customer.getPassword() == password)
        {
            return true; // Login successful
        }
    }
    return false;
}
bool UserAuth::adminLogin(const std::string &username, const std::string &password)
{
    return username == "admin" && password == "168168";
}
bool UserAuth::registerUser(const std::string &username, const std::string &password,
                            const std::string &name, const std::string &gender,
                            int age, const std::string &phone)
{
    for (const auto &customer : customers)
    {
        if (customer.getUsername() == username)
        {
            return false;
        }
    }
    customers.emplace_back(username, password, name, gender, age, phone);
    saveUsersToFile("customers.xlsx");
    return true;
}

void UserAuth::loadUsersFromFile(const std::string &filename)
{
    customers = loadFromFile(filename);
}

void UserAuth::saveUsersToFile(const std::string &filename)
{
    saveToFile(customers, filename);
}
