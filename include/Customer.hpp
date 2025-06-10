#pragma once
#include <string>

class Customer
{
private:
    std::string name, gender, room, phone;
    int age;

public:
    Customer(std::string name, std::string gender, int age, std::string room, std::string phone);

    std::string getName() const;
    std::string getGender() const;
    std::string getRoom() const;
    std::string getPhone() const;
    int getAge() const;

    void setName(std::string name);
    void setAge(int age);
    void displayRow() const;
};