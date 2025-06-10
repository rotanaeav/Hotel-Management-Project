#include <iostream>
#include "MenuUtils.hpp"

void showMainMenu()
{
    std::cout << "\n\033[1;35m==== Welcome to Hotel System ====\033[0m\n";
    std::cout << "1. Login\n";
    std::cout << "2. Register\n";
    std::cout << "3. Exit\n";
}

void showAdminMenu()
{
    std::cout << "\n\033[1;36m--- ADMIN MENU ---\033[0m\n";
    std::cout << "1. Add Customer\n";
    std::cout << "2. View All Customers\n";
    std::cout << "3. Delete Customer\n";
    std::cout << "4. Search Customer\n";
    std::cout << "5. Update Customer\n";
    std::cout << "6. Sort Customers\n";
    std::cout << "7. Logout\n";
}

void showUserMenu()
{
    std::cout << "\n\033[1;36m--- MENU ---\033[0m\n";
    std::cout << "1. Show Room List\n";
    std::cout << "2. Book Room\n";
    std::cout << "3. Exit\n";
}
