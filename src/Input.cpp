#include "Input.hpp"
#include "Validation.hpp"
#include "Customer.hpp"
#include <iostream>
#include <vector>
#include <tabulate/table.hpp>
#include "color.hpp"
using namespace tabulate;

Customer input(const std::vector<Customer> &existingCustomers)
{
    system("cls");

    std::cout << YELLOW << " ____  _____ ____ ___ ____ _____ _____ ____       _    ____ ____ ___  _   _ _   _ _____ " << std::endl;
    std::cout << "|  _ \\| ____/ ___|_ _/ ___|_   _| ____|  _ \\     / \\  / ___/ ___/ _ \\| | | | \\ | |_   _|" << std::endl;
    std::cout << "| |_) |  _|| |  _ | |\\___ \\ | | |  _| | |_) |   / _ \\| |  | |  | | | | | | |  \\| | | |  " << std::endl;
    std::cout << "|  _ <| |__| |_| || | ___) || | | |___|  _ <   / ___ \\ |__| |__| |_| | |_| | |\\  | | |  " << std::endl;
    std::cout << "|_| \\_\\_____\\____|___|____/ |_| |_____|_| \\_\\ /_/   \\_\\____\\____\\___/ \\___/|_| \\_| |_|  " << std::endl;
    std::cout << RESET << std::endl;

    std::string username, password, name, gender, phone;
    int age;
    
    do
    {
        std::cout << YELLOW << "|---> Enter Username: " << RESET;
        std::cin >> username;
        
        if (!isValidUsername(username))
        {
            std::cout << RED << "|---> Username must be at least 3 characters !\n"
                      << RESET;
        }
        else if (isUsernameFound(username, existingCustomers))
        {
            std::cout << RED << "|---> Username already exists! Please choose a different username ! \n"
                      << RESET;
        }
    } while (!isValidUsername(username) || isUsernameFound(username, existingCustomers));

    do
    {
        std::cout << YELLOW << "|---> Enter Password: " << RESET;
        std::cin >> password;
        if (!isValidPassword(password))
        {
            std::cout << RED << "|---> Password must be at least 4 characters !\n"
                      << RESET;
        }
    } while (!isValidPassword(password));

    do
    {
        std::cout << YELLOW << "|---> Enter Name: " << RESET;
        std::cin >> name;
        if (!isValidName(name))
        {
            std::cout << RED << "|---> Name cannot be empty !\n"
                      << RESET;
        }
    } while (!isValidName(name));

    do
    {
        std::cout << YELLOW << "|---> Enter Gender (Male/Female/M/F/Other): " << RESET;
        std::cin >> gender;
        if (!isValidGender(gender))
        {
            std::cout << RED << "|---> Gender must be 'Male', 'Female', or 'Other' !\n"
                      << RESET;
        }
    } while (!isValidGender(gender));

    do
    {
        std::cout << YELLOW << "|---> Enter Age: " << RESET;
        std::cin >> age;
        if (!isValidAge(age))
        {
            std::cout << RED << "|---> Age must be between 18 and 120 !\n"
                      << RESET;
        }
    } while (!isValidAge(age));

    do
    {
        std::cout << YELLOW << "|---> Enter Phone (8-15 digits): " << RESET;
        std::cin >> phone;
        if (!isValidPhone(phone))
        {
            std::cout << RED << "|---> Phone number must be 8-15 digits ! \n"
                      << RESET;
        }
    } while (!isValidPhone(phone));
    
            // Pause to let user see the result
        std::cout << YELLOW << "|---> Press Enter to continue..." << RESET;
        std::cin.ignore();
        std::cin.get();
        
    return Customer(username, password, name, gender, age, phone);
}