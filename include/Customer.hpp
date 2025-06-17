#pragma once
#include <string>

class Customer
{
private:
    std::string username, password;
    std::string name, gender, room, phone;
    int age;
    std::string id;
    static int idCounter;

public:
    Customer(std::string username, std::string password, std::string name,
              std::string gender, int age, std::string room, std::string phone);

    // get
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getName() const;
    std::string getGender() const;
    std::string getRoom() const;
    std::string getPhone() const;
    int getAge() const;
    std::string getId() const;

    // set
    void setName(std::string name);
    void setAge(int age);
    void setRoom(std::string room);

    void displayRow() const;
    static std::string generateId();
};
