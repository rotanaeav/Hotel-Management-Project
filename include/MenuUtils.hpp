#pragma once
#include <vector>
#include "Customer.hpp"
#include "Room.hpp"

void showAdminMenu();
void showUserMenu();
void showMainMenu();
void showRooms(const std::vector<Room> &rooms);

// struct Booking {
//     string customerName;
//     int roomNumber;
//     string checkInDate;
//     string checkOutDate;
// };
