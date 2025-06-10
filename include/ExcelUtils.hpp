#pragma once
#include <vector>
#include "Customer.hpp"
#include "Room.hpp"

void saveToFile(const std::vector<Customer> &customers, const std::string &filename);
std::vector<Customer> loadFromFile(const std::string &filename);
void roomToFile(const std::vector<Room> &rooms, const std::string &filename);
std::vector<Room> roomsFromFile(const std::string &filename);