#include <iostream>
#include <iomanip>
#include "MenuUtils.hpp"
#include "Input.hpp"
#include <tabulate/table.hpp>
#include "color.hpp"
using namespace tabulate;

void showMainMenu()
{
    system("cls");
    std::cout << YELLOW << "__        __   _                            _          _   _       _       _   ____            _                 " << std::endl;
    std::cout << "\\ \\      / /__| | ___ ___  _ __ ___   ___  | |_ ___   | | | | ___ | |_ ___| | / ___| _   _ ___| |_ ___ _ __ ___  " << std::endl;
    std::cout << " \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  | |_| |/ _ \\| __/ _ \\ | \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ " << std::endl;
    std::cout << "  \\ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) | |  _  | (_) | ||  __/ |  ___) | |_| \\__ \\ ||  __/ | | | | |" << std::endl;
    std::cout << "   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/  |_| |_|\\___/ \\__\\___|_| |____/ \\__, |___/\\__\\___|_| |_| |_|" << std::endl;
    std::cout << "                                                                                     |___/                       " << std::endl;
    std::cout << RESET;

    Table menuTable;
    menuTable.add_row({"Please Choose Options"});
    menuTable.add_row({"1. login Or Register"});
    menuTable.add_row({"2. Exit The Program"});
    menuTable.format()
        .font_style({FontStyle::bold})
        .border_left("|")
        .border_right("|")
        .border_top("-")
        .border_bottom("-");
    cout << BLUE << menuTable << RESET << std::endl;
}

void showAdminMenu()
{
    system("cls");
    std::cout << YELLOW << "        _    ____  __  __ ___ _   _      __  __ _____ _   _ _   _     " << std::endl;
    std::cout << "       / \\  |  _ \\|  \\/  |_ _| \\ | |    |  \\/  | ____| \\ | | | | |    " << std::endl;
    std::cout << "      / _ \\ | | | | |\\/| || ||  \\| |    | |\\/| |  _| |  \\| | | | |    " << std::endl;
    std::cout << " _   / ___ \\| |_| | |  | || || |\\  |    | |  | | |___| |\\  | |_| |  _ " << std::endl;
    std::cout << "(_) /_/   \\_\\____/|_|  |_|___|_| \\_|    |_|  |_|_____|_| \\_|\\___/  (_)" << std::endl;
    std::cout<<RESET<<std::endl;

    Table admin;
    admin.add_row({"1. Add Customer"});
    admin.add_row({"2. View All Customers"});
    admin.add_row({"3. Search Customer"});
    admin.add_row({"4. Edit Customer"});
    admin.add_row({"5. Delete Customer"});
    admin.add_row({"6. Sort Customers"});
    admin.add_row({"7. Assign Room to Customer"});
    admin.add_row({"8. Logout"});
    admin.format()
        .font_style({FontStyle::bold})
        .border_left("|")
        .border_right("|")
        .border_top("-")
        .border_bottom("-");
    cout << BLUE << admin << RESET << std::endl;
}

void showUserMenu()
{
    system("cls");
    std::cout<< YELLOW << " __  __ _____ _   _ _   _ " << std::endl;
    std::cout << "|  \\/  | ____| \\ | | | | |" << std::endl;
    std::cout << "| |\\/| |  _| |  \\| | | | |" << std::endl;
    std::cout << "| |  | | |___| |\\  | |_| |" << std::endl;
    std::cout << "|_|  |_|_____|_| \\_|\\___/ " << RESET<<std::endl;

    Table user;
    user.add_row({"1. Show Room List"});
    user.add_row({"2. Book Room"});
    user.add_row({"3. Exit"});
    user.format()
        .font_style({FontStyle::bold})
        .border_left("|")
        .border_right("|")
        .border_top("-")
        .border_bottom("-");
    cout << BLUE << user << RESET << std::endl;

}

void showRooms(const std::vector<Room> &rooms)
{
    system("cls");
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
            std::cout << "\033[1;32m"; // green
        }
        else
        {
            std::cout << "\033[1;31m"; // red
        }

        std::cout << std::setw(10) << room.getId()
                  << std::setw(10) << room.getType()
                  << std::setw(15) << (room.isAvailable() ? "Available" : "Not Available") << "\033[0m\n";
    }
}