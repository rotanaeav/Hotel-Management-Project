#include "Customer.hpp"
#include <iomanip>
#include <iostream>

int Customer::idCounter = 1;

// Constructor without room
Customer::Customer(std::string username, std::string password, std::string name,
                   std::string gender, int age, std::string phone)
    : username(username), password(password), name(name), gender(gender), age(age),
      phone(phone), room("")
{
  id = generateId();
  ++idCounter;
}

// Constructor with room (for loading from file)
Customer::Customer(std::string username, std::string password, std::string name,
                   std::string gender, int age, std::string phone, std::string room)
    : username(username), password(password), name(name), gender(gender), age(age),
      phone(phone), room(room)
{
  id = generateId();
  ++idCounter;
}

// Getter methods
std::string Customer::getUsername() const { return username; }
std::string Customer::getPassword() const { return password; }
std::string Customer::getName() const { return name; }
std::string Customer::getGender() const { return gender; }
std::string Customer::getRoom() const { return room; }
std::string Customer::getPhone() const { return phone; }
int Customer::getAge() const { return age; }
std::string Customer::getId() const { return id; }

// Setter methods
void Customer::setName(std::string name) { this->name = name; }
void Customer::setAge(int age) { this->age = age; }
void Customer::setRoom(std::string room) { this->room = room; }

// Static methods
std::string Customer::generateId()
{
  return "C" + std::to_string(idCounter);
}

void Customer::setIdCounter(int counter)
{
  idCounter = counter;
}

void Customer::displayRow() const
{
  std::cout << std::left << std::setw(15) << id
            << std::setw(20) << name
            << std::setw(10) << gender
            << std::setw(5) << age
            << std::setw(10) << (room.empty() ? "None" : room)
            << std::setw(15) << phone << "\n";
}