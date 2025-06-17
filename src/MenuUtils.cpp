#include <iostream>
#include <iomanip>
#include "MenuUtils.hpp"
#include "Input.hpp"

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
    std::cout << "\n";
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
    std::cout << "\n";
    std::cout << "1. Show Room List\n";
    std::cout << "2. Book Room\n";
    std::cout << "3. Exit\n";
}
void showRooms(const std::vector<Room> &rooms)
{
    std::cout << "\033[1;33m\nAvailable Rooms:\033[0m\n";
    std::cout << std::left
              << std::setw(10) << "Room ID"
              << std::setw(10) << "Type"
              << std::setw(15) << "Availability" << "\n";
    for (const auto &room : rooms)
    {
        std::cout << std::setw(10) << room.getId()
                  << std::setw(10) << room.getType()
                  << std::setw(15) << (room.isAvailable() ? "Available" : "Not Available") << "\n";
    }
}
void bookRoom(std::vector<Customer> &customers, std::vector<Room> &rooms)
{
    std::string roomId;
    std::cout << "Enter Room ID to book: ";
    std::cin >> roomId;

    auto it = std::find_if(rooms.begin(), rooms.end(), [&](const Room &r)
                           { return r.getId() == roomId; });

    if (it == rooms.end())
    {
        std::cout << "\033[1;31mRoom not found.\033[0m\n";
        return;
    }
    if (!it->isAvailable())
    {
        std::cout << "\033[1;31mRoom is not available.\033[0m\n";
        return;
    }
    Customer newCustomer = input();
    customers.push_back(newCustomer);
    it->setAvailable(false);
    std::cout << "\033[1;32mRoom booked successfully!\033[0m\n";
}

void userMenu(std::vector<Customer> &customers, std::vector<Room> &rooms)
{
    int choice;
    do
    {
        showUserMenu();
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            showRooms(rooms);
            break;
        case 2:
            bookRoom(customers, rooms);
            break;
        case 3:
            std::cout << "Exiting the user menu...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 3);
}
