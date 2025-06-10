#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Customer.hpp"
#include "Room.hpp"
#include "MenuUtils.hpp"
#include "ExcelUtils.hpp"
#include "User.hpp"
// our room:
std::vector<Room> initializeRooms(const std::string &filename)
{
    std::vector<Room> rooms = roomsFromFile(filename);
    // default
    if (rooms.empty())
    {
        rooms = {
            Room("R101", "Single", true),
            Room("R102", "Single", true),
            Room("R103", "Single", true),
            Room("R104", "Single", true)};
        roomToFile(rooms, filename);
    }

    return rooms;
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

    std::string name, gender, phone;
    int age;
    std::cout << "Enter Name: ";
    std::cin >> name;
    std::cout << "Enter Gender: ";
    std::cin >> gender;
    std::cout << "Enter Age: ";
    std::cin >> age;
    std::cout << "Enter Phone: ";
    std::cin >> phone;

    customers.emplace_back(name, gender, age, roomId, phone);
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
        }
    } while (choice != 3);
}

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
        {
            std::string name, gender, room, phone;
            int age;
            std::cout << "Enter Name: ";
            std::cin >> name;
            std::cout << "Enter Gender: ";
            std::cin >> gender;
            std::cout << "Enter Age: ";
            std::cin >> age;
            std::cout << "Enter Room: ";
            std::cin >> room;
            std::cout << "Enter Phone: ";
            std::cin >> phone;
            customers.emplace_back(name, gender, age, room, phone);
            break;
        }
        case 2: // View Customers

            break;
        case 3: // Delete Customer

            break;
        case 4: // Search Customer

            break;
        case 5: // Update Customer

            break;
        case 6: // Sort Customers (ID and ID room)

            break;
        case 7: // Logout
            return;
        }
    } while (true);
}

int main()
{
    std::vector<Customer> customers = loadFromFile("customers.xlsx");
    std::vector<Room> rooms = initializeRooms("rooms.xlsx");

    int option;
    do
    {
        showMainMenu();
        std::cout << "Choose: ";
        std::cin >> option;
        switch (option)
        {
        case 1:
            if (login("admin"))
            {
                adminMenu(customers);
            }
            else
            {
                std::cout << "\033[1;31mLogin failed.\033[0m\n";
            }
            break;
        case 2:
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
    } while (option != 3);

    saveToFile(customers, "customers.xlsx");
    roomToFile(rooms, "rooms.xlsx");
    return 0;
}
