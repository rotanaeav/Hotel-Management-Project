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
    std::cout << YELLOW << "__        _______ _     ____ ___  __  __ _____    _____ ___     _   _  ___ _____ _____ _        ______   ______ _____ _____ __  __ " << std::endl;
    std::cout << "\\ \\      / / ____| |   / ___/ _ \\|  \\/  | ____|  |_   _/ _ \\   | | | |/ _ \\_   _| ____| |      / ___\\ \\ / / ___|_   _| ____|  \\/  |" << std::endl;
    std::cout << " \\ \\ /\\ / /|  _| | |  | |  | | | | |\\/| |  _|      | || | | |  | |_| | | | || | |  _| | |      \\___ \\\\ V /\\___ \\ | | |  _| | |\\/| |" << std::endl;
    std::cout << "  \\ V  V / | |___| |__| |__| |_| | |  | | |___     | || |_| |  |  _  | |_| || | | |___| |___    ___) || |  ___) || | | |___| |  | |" << std::endl;
    std::cout << "   \\_/\\_/  |_____|_____\\____\\___/|_|  |_|_____|    |_| \\___/   |_| |_|\\___/ |_| |_____|_____|  |____/ |_| |____/ |_| |_____|_|  |_|" << std::endl;
    std::cout << RESET;

    Table menuTable;
    menuTable.add_row({" Please Choose Options"});
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
    std::cout << YELLOW << "    _    ____  __  __ ___ _   _      __  __ _____ _   _ _   _     " << std::endl;
    std::cout << "   / \\  |  _ \\|  \\/  |_ _| \\ | |    |  \\/  | ____| \\ | | | | |    " << std::endl;
    std::cout << "  / _ \\ | | | | |\\/| || ||  \\| |    | |\\/| |  _| |  \\| | | | |    " << std::endl;
    std::cout << " / ___ \\| |_| | |  | || || |\\  |    | |  | | |___| |\\  | |_| |   " << std::endl;
    std::cout << "/_/   \\_\\____/|_|  |_|___|_| \\_|    |_|  |_|_____|_| \\_|\\___/  " << std::endl;
    std::cout << RESET << std::endl;

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
    std::cout << YELLOW << " __  __ _____ _   _ _   _ " << std::endl;
    std::cout << "|  \\/  | ____| \\ | | | | |" << std::endl;
    std::cout << "| |\\/| |  _| |  \\| | | | |" << std::endl;
    std::cout << "| |  | | |___| |\\  | |_| |" << std::endl;
    std::cout << "|_|  |_|_____|_| \\_|\\___/ " << RESET << std::endl;

    Table user;
    user.add_row({"1. Show Room List"});
    user.add_row({"2. Book Room"});
    user.add_row({"3. Show Book Room"});
    user.add_row({"4. Exit"});
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
            std::cout << GREEN;
        }
        else
        {
            std::cout << RED;
        }

        std::cout << std::setw(10) << room.getId()
                  << std::setw(10) << room.getType()
                  << std::setw(15) << (room.isAvailable() ? "Available" : "Not Available") << "\033[0m\n";
    }
}

/* void showBookings(const vector<Booking>& bookings) {
    cout << "\n=== Room Bookings ===\n";
    for (const auto& booking : bookings) {
        cout << "Customer Name: " << booking.customerName << endl;
        cout << "Room Number: " << booking.roomNumber << endl;
        cout << "Check-In Date: " << booking.checkInDate << endl;
        cout << "Check-Out Date: " << booking.checkOutDate << endl;
        cout << "--------------------------\n";
    }
}
*/