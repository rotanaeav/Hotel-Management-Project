#ifndef VALIDATION_HPP
#define VALIDATION_HPP

#include <string>
#include <vector>

// Forward declaration
class Customer;

// Existing validation functions
bool isValidUsername(const std::string &username);
bool isValidPassword(const std::string &password);
bool isValidName(const std::string &name);
bool isValidGender(const std::string &gender);
bool isValidAge(int age);
bool isValidPhone(const std::string &phone);
bool confirmYesNo(const std::string &message);
int getValidatedChoice(int min, int max);

// New username checking function
bool isUsernameFound(const std::string &username, const std::vector<Customer> &customers);

#endif