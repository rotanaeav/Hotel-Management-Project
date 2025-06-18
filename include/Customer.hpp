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
    // Constructor without room (for new customers)
    Customer(std::string username, std::string password, std::string name,
             std::string gender, int age, std::string phone);
    
    // Constructor with room (for loading from file)
    Customer(std::string username, std::string password, std::string name,
             std::string gender, int age, std::string phone, std::string room);

    // Get methods
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getName() const;
    std::string getGender() const;
    std::string getRoom() const;
    std::string getPhone() const;
    int getAge() const;
    std::string getId() const;
    
    // Set methods
    void setName(std::string name);
    void setAge(int age);
    void setRoom(std::string room);
    
    // Static methods
    static std::string generateId();
    static void setIdCounter(int counter); // For loading from file
    
    // Display method
    void displayRow() const;
};