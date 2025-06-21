#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "Customer.hpp"
#include "Room.hpp"
#include "MenuUtils.hpp"
#include "ExcelUtils.hpp"
#include "User.hpp"
#include "Input.hpp"
#include <tabulate/table.hpp>
#include "Color.hpp"
using namespace tabulate;

// Init room
std::vector<Room> initializeRooms(const std::string &filename)
{
    std::vector<Room> rooms = roomsFromFile(filename);
    // default if no rooms loaded
    if (rooms.empty())
    {
        rooms = {
            Room("R101", "Single", true),
            Room("R102", "Single", true),
            Room("R103", "Single", true),
            Room("R104", "Single", true),
            Room("R201", "Double", true),
            Room("R202", "Double", true),
            Room("R301", "Suite", true),
            Room("R302", "Suite", true)};
        roomToFile(rooms, filename); // Save rooms to file
    }
    return rooms;
}

void showCustomers(const std::vector<Customer> &customers, int pageSize = 5)
{
    if (customers.empty())
    {
        std::cout << "\033[1;31mNo customers found.\033[0m\n";
        return;
    }

    int totalPages = (customers.size() + pageSize - 1) / pageSize;
    int currentPage = 0;
    char next;

    do
    {
        system("cls");
        std::cout << "\033[1;33mCustomer List (Page " << currentPage + 1 << " of " << totalPages << "):\033[0m\n";

        // Header
        std::cout << "\033[1;36m" << std::left
                  << std::setw(15) << "Customer ID"
                  << std::setw(20) << "Name"
                  << std::setw(10) << "Gender"
                  << std::setw(5) << "Age"
                  << std::setw(10) << "Room"
                  << std::setw(15) << "Phone" << "\033[0m\n";
        std::cout << "\033[1;37m---------------------------------------------------------------------\033[0m\n";

        int start = currentPage * pageSize;
        int end = std::min(start + pageSize, (int)customers.size());

        for (int i = start; i < end; ++i)
        {
            customers[i].displayRow();
        }

        std::cout << "\n\033[1;36mPress n for next, p for previous, q to quit: \033[0m";
        std::cin >> next;

        if (next == 'n' && currentPage < totalPages - 1)
            ++currentPage;
        else if (next == 'p' && currentPage > 0)
            --currentPage;
        else if (next == 'q')
            break;

    } while (true);
}

void deleteCustomer(std::vector<Customer> &customers, std::vector<Room> &rooms)
{
    std::string input;
    std::cout << YELLOW << "Enter Customer Name or ID to delete: " << RESET;
    std::cin >> input;

    auto it = std::find_if(customers.begin(), customers.end(),
                           [&input](const Customer &c)
                           {
                               return c.getName() == input || c.getId() == input;
                           });

    if (it != customers.end())
    {
        // Free up the room if customer had one
        std::string roomId = it->getRoom();
        if (!roomId.empty())
        {
            auto roomIt = std::find_if(rooms.begin(), rooms.end(),
                                       [&roomId](Room &r)
                                       {
                                           return r.getId() == roomId;
                                       });
            if (roomIt != rooms.end())
            {
                roomIt->setAvailable(true);
            }
        }

        customers.erase(it);
        saveToFile(customers, "customers.xlsx");
        roomToFile(rooms, "rooms.xlsx");
        std::cout << "\033[1;32mCustomer deleted successfully!\033[0m\n";
    }
    else
    {
        std::cout << "\033[1;31mCustomer not found!\033[0m\n";
    }
}

void searchCustomer(const std::vector<Customer> &customers)
{
    std::string input;
    std::cout << YELLOW << "Enter Customer ID or Name to search: " << RESET;
    std::cin >> input;

    bool found = false;
    for (const auto &c : customers)
    {
        if (c.getId() == input || c.getName() == input)
        {
            std::cout << "\n\033[1;33mCustomer Found:\033[0m\n";
            std::cout << "\033[1;36m" << std::left << std::setw(15) << "Customer ID"
                      << std::setw(20) << "Name"
                      << std::setw(10) << "Gender"
                      << std::setw(5) << "Age"
                      << std::setw(10) << "Room"
                      << std::setw(15) << "Phone" << "\033[0m\n";
            std::cout << "\033[1;37m---------------------------------------------------------------------\033[0m\n";
            c.displayRow();
            found = true;
            break;
        }
    }

    if (!found)
    {
        std::cout << "\033[1;31mCustomer not found.\033[0m\n";
    }
}

void updateCustomer(std::vector<Customer> &customers)
{
    std::string id;
    std::cout << YELLOW << "Enter Customer ID to update: " << RESET;
    std::cin >> id;

    for (auto &c : customers)
    {
        if (c.getId() == id)
        {
            std::cout << YELLOW << "Current Name: " << c.getName() << "\n"
                      << RESET;
            std::cout << YELLOW << "Enter new name (or '.' to keep current): " << RESET;
            std::string newName;
            std::cin >> newName;
            if (newName != ".")
                c.setName(newName);

            std::cout << YELLOW << "Current Age: " << c.getAge() << "\n"
                      << RESET;
            std::cout << YELLOW << "Enter new age (or -1 to keep current): " << RESET;
            int newAge;
            std::cin >> newAge;
            if (newAge != -1)
                c.setAge(newAge);

            saveToFile(customers, "customers.xlsx");
            std::cout << "\033[1;32mCustomer updated successfully.\033[0m\n";
            return;
        }
    }
    std::cout << "\033[1;31mCustomer not found.\033[0m\n";
}

void assignRoomToCustomer(std::vector<Customer> &customers, std::vector<Room> &rooms)
{
    std::string customerId, roomId;

    std::cout << "Enter Customer ID: ";
    std::cin >> customerId;

    // Find customer
    auto customerIt = std::find_if(customers.begin(), customers.end(),
                                   [&customerId](Customer &c)
                                   {
                                       return c.getId() == customerId;
                                   });

    if (customerIt == customers.end())
    {
        std::cout << "\033[1;31mCustomer not found!\033[0m\n";
        return;
    }

    // Show available rooms
    std::cout << "\n\033[1;33mAvailable Rooms:\033[0m\n";
    showRooms(rooms);

    std::cout << YELLOW << "\nEnter Room ID to assign: " << RESET;
    std::cin >> roomId;

    // Find room
    auto roomIt = std::find_if(rooms.begin(), rooms.end(),
                               [&roomId](const Room &r)
                               {
                                   return r.getId() == roomId;
                               });

    if (roomIt == rooms.end())
    {
        std::cout << "\033[1;31mRoom not found!\033[0m\n";
        return;
    }

    if (!roomIt->isAvailable())
    {
        std::cout << "\033[1;31mRoom is not available!\033[0m\n";
        return;
    }

    // Free up previous room if customer had one
    std::string oldRoom = customerIt->getRoom();
    if (!oldRoom.empty())
    {
        auto oldRoomIt = std::find_if(rooms.begin(), rooms.end(),
                                      [&oldRoom](Room &r)
                                      {
                                          return r.getId() == oldRoom;
                                      });
        if (oldRoomIt != rooms.end())
        {
            oldRoomIt->setAvailable(true);
        }
    }

    // Assign new room
    customerIt->setRoom(roomId);
    roomIt->setAvailable(false);

    saveToFile(customers, "customers.xlsx");
    roomToFile(rooms, "rooms.xlsx");

    std::cout << "\033[1;32mRoom " << roomId << " assigned to customer " << customerId << " successfully!\033[0m\n";
}

void sortCustomers(std::vector<Customer> &customers)
{
    if (customers.empty())
    {
        std::cout << "\033[1;31mNo customers to sort.\033[0m\n";
        return;
    }

    int option;
    std::cout << YELLOW << "Sort by:\n1. Customer ID\n2. Name\n3. Room ID\nEnter choice: " << RESET;
    std::cin >> option;

    if (option == 1)
    {
        std::sort(customers.begin(), customers.end(), [](const Customer &a, const Customer &b)
                  { return a.getId() < b.getId(); });
    }
    else if (option == 2)
    {
        std::sort(customers.begin(), customers.end(), [](const Customer &a, const Customer &b)
                  { return a.getName() < b.getName(); });
    }
    else if (option == 3)
    {
        std::sort(customers.begin(), customers.end(), [](const Customer &a, const Customer &b)
                  { return a.getRoom() < b.getRoom(); });
    }
    else
    {
        std::cout << GREEN << "Invalid option." << RESET;
        return;
    }

    std::cout << GREEN << "Customers sorted successfully." << RESET;
    showCustomers(customers);
    saveToFile(customers, "customers.xlsx");
}

void bookRoom(std::vector<Customer> &customers, std::vector<Room> &rooms)
{
    std::string roomId;

    // Show available rooms first
    std::cout << GREEN << "Available Rooms:" << RESET;
    showRooms(rooms);

    std::cout << YELLOW << "\nEnter Room ID to book: " << RESET;
    std::cin >> roomId;

    auto it = std::find_if(rooms.begin(), rooms.end(), [&](Room &r)
                           { return r.getId() == roomId; });

    if (it == rooms.end())
    {
        std::cout << RED << "Room not found." << RESET;
        return;
    }
    if (!it->isAvailable())
    {
        std::cout << RED << "Room is not available." << RESET;
        return;
    }

    Customer newCustomer = input();
    newCustomer.setRoom(roomId);
    customers.push_back(newCustomer);
    it->setAvailable(false);

    saveToFile(customers, "customers.xlsx");
    roomToFile(rooms, "rooms.xlsx");

    std::cout << GREEN << "Room booked successfully!" << RESET;
}

void adminMenu(std::vector<Customer> &customers, std::vector<Room> &rooms)
{
    int choice;
    do
    {
        showAdminMenu();
        std::cout << YELLOW << "Enter choice: " << RESET;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Customer newCustomer = input();
            customers.push_back(newCustomer);
            saveToFile(customers, "customers.xlsx");
            std::cout << GREEN << "Customer added successfully!" << RESET;
            break;
        }
        case 2:
        {
            showCustomers(customers);
            break;
        }
        case 3:
        {
            searchCustomer(customers);
            break;
        }
        case 4:
        {
            updateCustomer(customers);
            break;
        }
        case 5:
        {
            deleteCustomer(customers, rooms);
            break;
        }
        case 6:
        {
            sortCustomers(customers);
            break;
        }
        case 7:
        {
            assignRoomToCustomer(customers, rooms);
            break;
        }
        case 8: // Logout
            return;
        default:
            std::cout << RED << "Invalid choice. Please try again.\n"
                      << RESET;
            break;
        }

        // Pause to let user see the result
        std::cout << GREEN << "\nPress Enter to continue..." << RESET;
        std::cin.ignore();
        std::cin.get();

    } while (true);
}

void userMenu(std::vector<Customer> &customers, std::vector<Room> &rooms)
{
    int choice;
    do
    {
        showUserMenu();
        std::cout << YELLOW << "Enter choice: " << RESET;
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
            std::cout << GREEN << "Exiting the user menu...\n"
                      << RESET;
            break;
        default:
            std::cout << RED << "Invalid choice. Please try again.\n"
                      << RESET;
            break;
        }

        if (choice != 3)
        {
            std::cout << GREEN << "\nPress Enter to continue..." << RESET;
            std::cin.ignore();
            std::cin.get();
        }

    } while (choice != 3);
}

bool loginRegister(UserAuth &userAuth, std::vector<Customer> &customers, std::vector<Room> &rooms)
{
    std::string username, password;
    std::cout << YELLOW << "Enter Username: " << RESET;
    std::cin >> username;
    std::cout << YELLOW << "Enter Password: " << RESET;
    std::cin >> password;

    if (userAuth.adminLogin(username, password))
    {
        std::cout << GREEN << "Admin Login successful!\n"
                  << RESET;
        adminMenu(customers, rooms);
        return true;
    }

    else if (userAuth.login(username, password))
    {
        std::cout << GREEN << "User Login successful!\n"
                  << RESET;
        userMenu(customers, rooms);
        return true;
    }
    else
    {
        // register
        std::cout << RED << "Login failed. Do you want to register? (y/n): " << RESET;
        char registerChoice;
        std::cin >> registerChoice;

        if (registerChoice == 'y' || registerChoice == 'Y')
        {
            Customer newCustomer = input();
            if (userAuth.registerUser(newCustomer.getUsername(), newCustomer.getPassword(),
                                      newCustomer.getName(), newCustomer.getGender(),
                                      newCustomer.getAge(), newCustomer.getPhone()))
            {
                std::cout << GREEN << "Registration successful!\n"
                          << RESET;
                userMenu(customers, rooms);
                return true;
            }
            else
            {
                std::cout << YELLOW << "Username already exists.\n"
                          << RESET;
                return false;
            }
        }
    }

    return false;
}

int main()
{
    system("cls");
    UserAuth userAuth;

    std::vector<Room> rooms = initializeRooms("rooms.xlsx");
    std::vector<Customer> customers = loadFromFile("customers.xlsx");

    int option;
    do
    {
        showMainMenu();
        std::cout << YELLOW << "Choose: " << RESET;
        std::cin >> option;

        switch (option)
        {
        case 1:
        {
            bool isLogin = loginRegister(userAuth, customers, rooms);
            if (!isLogin)
            {
                std::cout << RED << "Login failed. Please try again.\n"
                          << RESET;
            }
            break;
        }
        case 2:
            std::cout << GREEN << "Exiting the program...\n"
                      << RESET;
            break;
        default:
            std::cout << RED << "Invalid option. Please try again.\n"
                      << RESET;
            break;
        }

        if (option != 2)
        {
            std::cout << YELLOW << "\nPress Enter to continue..." << RESET;
            std::cin.ignore();
            std::cin.get();
        }

    } while (option != 2);

    saveToFile(customers, "customers.xlsx");
    roomToFile(rooms, "rooms.xlsx");

    return 0;
}