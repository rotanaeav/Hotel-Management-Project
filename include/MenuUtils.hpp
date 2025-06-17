#pragma once
#include <vector>
#include "Customer.hpp"
#include "Room.hpp"

void showAdminMenu();
void showUserMenu();
void showMainMenu();
void userMenu(std::vector<Customer> &customers, std::vector<Room> &rooms);
void adminMenu(std::vector<Customer> &customers);