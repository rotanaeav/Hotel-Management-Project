#include "Customer.hpp"
#include <iostream>
#include <iomanip>

Customer::Customer(std::string name, std::string gender, int age, std::string room, std::string phone)
    : name(name), gender(gender), age(age), room(room), phone(phone) {}

std::string Customer::getName() const { return name; }
std::string Customer::getGender() const { return gender; }
std::string Customer::getRoom() const { return room; }
std::string Customer::getPhone() const { return phone; }
int Customer::getAge() const { return age; }

void Customer::setName(std::string name) { this->name = name; }
void Customer::setAge(int age) { this->age = age; }

void Customer::displayRow() const
{
    std::cout << std::left << std::setw(10) << name
              << std::setw(8) << gender
              << std::setw(6) << age
              << std::setw(8) << room
              << std::setw(12) << phone << "\n";
}
