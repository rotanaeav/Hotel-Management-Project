#include "Validation.hpp"
#include "color.hpp"
#include "Customer.hpp"
#include <regex>
#include <iostream>
#include <vector>

bool isValidUsername(const std::string &username)
{
    return username.length() >= 3;
}

bool isValidPassword(const std::string &password)
{
    return password.length() >= 4;
}

bool isValidName(const std::string &name)
{
    return !name.empty();
}

bool isValidGender(const std::string &gender)
{
    return gender == "Male" || gender == "Female" || gender == "Other";
}

bool isValidAge(int age)
{
    return age >= 18 && age <= 120;
}

bool isValidPhone(const std::string &phone)
{
    std::regex pattern("^\\d{8,15}$");
    return std::regex_match(phone, pattern);
}

bool confirmYesNo(const std::string &message)
{
    char response;
    std::cout << message << " (y/n): ";
    std::cin >> response;
    return response == 'y' || response == 'Y';
}

int getValidatedChoice(int min, int max)
{
    int choice;
    while (true)
    {
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << RED << "=====> Invalid input. Please enter a number between <====="
                      << min << " and " << max << ": \033[0m";
        }
        else if (choice < min || choice > max)
        {
            std::cout << RED << "=====> Out of range. Enter a number between <====="
                      << min << " and " << max << ": \033[0m";
        }
        else
        {
            return choice;
        }
    }
}
bool isUsernameFound(const std::string &username, const std::vector<Customer> &customers)
{
    for (const auto &customer : customers)
    {
        if (customer.getUsername() == username)
        {
            return true;
        }
    }
    return false;
}