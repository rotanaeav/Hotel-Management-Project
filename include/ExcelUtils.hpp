#pragma once
#include <vector>
#include "Customer.hpp"

void saveToFile(const std::vector<Customer>& customers, const std::string& filename);
std::vector<Customer> loadFromFile(const std::string& filename);
