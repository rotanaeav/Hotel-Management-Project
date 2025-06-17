#include "Input.hpp"
#include <iostream>
#include <string>
Customer input()
{
    std::string username, password, name, gender, room, phone;
    int age;

    std::cout << "Enter Username: ";
    std::cin >> username;
    std::cout << "Enter Password: ";
    std::cin >> password;
    std::cout << "Enter Name: ";
    std::cin >> name;
    std::cout << "Enter Gender: ";
    std::cin >> gender;
    std::cout << "Enter Age: ";
    std::cin >> age;
    std::cout << "Enter Room: ";
    std::cin >> room;
    std::cout << "Enter Phone: ";
    std::cin >> phone;
    return Customer(username, password, name, gender, age, room, phone);
}
