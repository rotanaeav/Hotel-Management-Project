#include "Customer.hpp"
#include <iomanip>
#include <iostream>

int Customer::idCounter = 1;

Customer::Customer(std::string username, std::string password, std::string name,
                   std::string gender, int age, std::string phone)
    : username(username), password(password), name(name), gender(gender), age(age),
      phone(phone), room(""){
    id = generateId();
    ++idCounter;
}
std::string Customer::getUsername() const { return username; }
std::string Customer::getPassword() const { return password; }
std::string Customer::getName() const { return name; }
std::string Customer::getGender() const { return gender; }
std::string Customer::getRoom() const { return room; }
std::string Customer::getPhone() const { return phone; }
int Customer::getAge() const { return age; }
std::string Customer::getId() const { return id; }
//set
void Customer::setName(std::string name) { this->name = name; }
void Customer::setAge(int age) { this->age = age; }
void Customer::setRoom(std::string room) { this->room = room; } 
std::string Customer::generateId() {
    return "CUST" + std::to_string(idCounter);
}

void Customer::displayRow() const {
    std::cout << std::left << std::setw(15) << id
              << std::setw(20) << name
              << std::setw(10) << gender
              << std::setw(5) << age
              << std::setw(10) << room
              << std::setw(15) << phone << "\n";
}
