#include <iostream>
#include <iomanip>
#include <vector>
#include "Customer.hpp"
#include "Room.hpp"
#include "MenuUtils.hpp"
#include "ExcelUtils.hpp"
#include "User.hpp"
#include "Input.hpp"
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
            Room("R104", "Single", true)};
        roomToFile(rooms, filename); // Save rooms to file
    }
    return rooms;
}

void showCustomers(const std::vector<Customer> &customers, int pageSize = 5)
{
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
    newCustomer.setRoom(roomId);
    customers.push_back(newCustomer);
    it->setAvailable(false);
    std::cout << "\033[1;32mRoom booked successfully!\033[0m\n";
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
            Customer newCustomer = input();
            customers.push_back(newCustomer);
            saveToFile(customers, "customers.xlsx");
            std::cout << "\033[1;32mCustomer added successfully!\033[0m\n";
            break;
        }
        case 2:
        {
            showCustomers(customers);
            break;
        }
        case 3:
            // search customer
            break;
        case 4:
            // edit Customer
            break;
        case 5:
            // Delete Customer
            break;
        case 6:
            // Sort
            break;
        case 7: // Logout
            return;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (true);
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
bool loginRegister(UserAuth &userAuth, std::vector<Customer> &customers, std::vector<Room> &rooms)
{
    std::string username, password;
    std::cout << "Enter Username: ";
    std::cin >> username;
    std::cout << "Enter Password: ";
    std::cin >> password;
    if (userAuth.adminLogin(username, password))
    {
        std::cout << "Admin Login successful!\n";
        adminMenu(customers);
        return true;
    }

    if (userAuth.login(username, password))
    {
        std::cout << "User Login successful!\n";
        userMenu(customers, rooms);
        return true;
    }
    // register
    std::cout << "Login failed. Do you want to register? (y/n): ";
    char registerChoice;
    std::cin >> registerChoice;

    if (registerChoice == 'y' || registerChoice == 'Y')
    {
        Customer newCustomer = input();
        if (userAuth.registerUser(newCustomer.getUsername(), newCustomer.getPassword(),
                                  newCustomer.getName(), newCustomer.getGender(),
                                  newCustomer.getAge(), newCustomer.getPhone()))
        {
            std::cout << "Registration successful!\n";
            userMenu(customers, rooms);
            return true;
        }
        else
        {
            std::cout << "Username already exists.\n";
            return false;
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
        std::cout << "Choose: ";
        std::cin >> option;

        switch (option)
        {
        case 1:
        {
            bool isLogin = loginRegister(userAuth, customers, rooms);
            if (!isLogin)
            {
                std::cout << "Login failed. Please try again.\n";
            }
            break;
        }

        break;

        case 2:
            std::cout << "Exiting the program...\n";
            break;

        default:
            std::cout << "Invalid option. Please try again.\n";
            break;
        }
    }

    while (option != 2);
    saveToFile(customers, "customers.xlsx");
    roomToFile(rooms, "rooms.xlsx");

    return 0;
}
