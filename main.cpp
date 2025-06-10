#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Customer.hpp"
#include "Room.hpp"
#include "MenuUtils.hpp"
#include "ExcelUtils.hpp"
#include "User.hpp"

// Initialize a static list of rooms
std::vector<Room> initializeRooms()
{
    return {
        Room("R101", "Single", true),
        Room("R102", "Single", true),
        Room("R103", "Single", true),
        Room("R104", "Single", true)};
}

// Display room availability
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

// Book a room for a new customer
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

    // Collect customer info
    std::string name, id, gender, phone;
    int age;
    std::cout << "Enter Name: ";
    std::cin >> name;
    std::cout << "Enter ID: ";
    std::cin >> id;
    std::cout << "Enter Gender: ";
    std::cin >> gender;
    std::cout << "Enter Age: ";
    std::cin >> age;
    std::cout << "Enter Phone: ";
    std::cin >> phone;

    // Create customer and mark room booked
    customers.emplace_back(name, id, gender, age, roomId, phone);
    it->setAvailability(false);
    std::cout << "\033[1;32mRoom booked successfully!\033[0m\n";
}

// Menu for regular users
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
        }
    } while (choice != 3);
}

// Menu for admin users
void adminMenu(std::vector<Customer> &customers)
{
    int choice;
    do
    {
        showAdminMenu();
        std::cout << "Enter choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        { // Add Customer
            std::string name, id, gender, room, phone;
            int age;
            std::cout << "Enter Name: ";
            std::cin >> name;
            std::cout << "Enter ID: ";
            std::cin >> id;
            std::cout << "Enter Gender: ";
            std::cin >> gender;
            std::cout << "Enter Age: ";
            std::cin >> age;
            std::cout << "Enter Room: ";
            std::cin >> room;
            std::cout << "Enter Phone: ";
            std::cin >> phone;
            customers.emplace_back(name, id, gender, age, room, phone);
            break;
        }
        case 2: // View Customers
            // displayPaginatedCustomers(customers);
            break;
        case 3:
        { // Delete Customer
            std::string delId;
            std::cout << "Enter ID to delete: ";
            std::cin >> delId;
            // deleteCustomer(customers, delId);
            break;
        }
        case 4: // Search Customer
            // searchCustomer(customers);
            break;
        case 5: // Update Customer
            // updateCustomer(customers);
            break;
        case 6: // Sort Customers
            // sortCustomers(customers);
            break;
        case 7: // Logout
            return;
        }
    } while (true);
}

int main()
{
    // Load existing customers and initialize rooms
    std::vector<Customer> customers = loadFromFile("customers.xlsx");
    std::vector<Room> rooms = initializeRooms();

    int mainChoice;
    do
    {
        showMainMenu();
        std::cout << "Choose: ";
        std::cin >> mainChoice;
        switch (mainChoice)
        {
        case 1: // Admin Login
            if (login("admin"))
            {
                adminMenu(customers);
            }
            else
            {
                std::cout << "\033[1;31mLogin failed.\033[0m\n";
            }
            break;
        case 2: // User Register/Login
            if (registerOrLoginUser())
            {
                userMenu(customers, rooms);
            }
            else
            {
                std::cout << "\033[1;31mLogin failed.\033[0m\n";
            }
            break;
        }
    } while (mainChoice != 3);

    // Save before exit
    saveToFile(customers, "customers.xlsx");
    return 0;
}
