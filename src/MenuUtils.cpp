#include <iostream>
#include <iomanip>
#include "MenuUtils.hpp"
#include "Input.hpp"

void showMainMenu()
{
    std::cout << "\n\033[1;35m==== Welcome to Hotel System ====\033[0m\n";
    std::cout << "1. Login/Register\n";
    std::cout << "2. Exit\n";
}

void showAdminMenu()
{
    std::cout << "\n\033[1;36m--- ADMIN MENU ---\033[0m\n";
    std::cout << "\n";
    std::cout << "1. Add Customer\n";
    std::cout << "2. View All Customers\n";
    std::cout << "3. Search Customer\n";
    std::cout << "4. Edit Customer\n";
    std::cout << "5. Delete Customer\n";
    std::cout << "6. Sort Customers\n";
    std::cout << "7. Assign Room to Customer\n";
    std::cout << "8. Logout\n";
}

void showUserMenu()
{
    std::cout << "\n\033[1;36m--- MENU ---\033[0m\n";
    std::cout << "\n";
    std::cout << "1. Show Room List\n";
    std::cout << "2. Book Room\n";
    std::cout << "3. Exit\n";
}

void showRooms(const std::vector<Room> &rooms)
{
    std::cout << "\033[1;33m\nRoom List:\033[0m\n";
    std::cout << "\033[1;36m" << std::left
              << std::setw(10) << "Room ID"
              << std::setw(10) << "Type"
              << std::setw(15) << "Availability" << "\033[0m\n";
    std::cout << "\033[1;37m-------------------------------------\033[0m\n";
    
    for (const auto &room : rooms)
    {
        if (room.isAvailable())
        {
            std::cout << "\033[1;32m";//green
        }
        else
        {
            std::cout << "\033[1;31m"; //red
        }
        
        std::cout << std::setw(10) << room.getId()
                  << std::setw(10) << room.getType()
                  << std::setw(15) << (room.isAvailable() ? "Available" : "Not Available") << "\033[0m\n";
    }
}