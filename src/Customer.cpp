#include "Customer.hpp"
#include <iostream>
#include <iomanip>

// init id:
int Customer::idCounter = 1;

Customer::Customer(std::string name, std::string gender, int age, std::string room, std::string phone)
    : name(name), gender(gender), age(age), room(room), phone(phone)
{
    std::ostringstream oss;
    oss << "C" << std::setw(3) << std::setfill('0') << idCounter++;
    id = oss.str();
}

std::string Customer::getId() const { return id; }
std::string Customer::getName() const { return name; }
std::string Customer::getGender() const { return gender; }
std::string Customer::getRoom() const { return room; }
std::string Customer::getPhone() const { return phone; }
int Customer::getAge() const { return age; }

void Customer::setName(std::string name) { this->name = name; }
void Customer::setAge(int age) { this->age = age; }

void Customer::displayRow() const
{
    std::cout << std::left << std::setw(15) << id
              << std::setw(20) << name
              << std::setw(10) << gender
              << std::setw(5) << age
              << std::setw(10) << room
              << std::setw(15) << phone << "\n";
}
