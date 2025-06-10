#pragma once
#include <string>

class Room
{
private:
    std::string id;
    std::string type;
    bool available;

public:
    Room(std::string id, std::string type, bool available);

    std::string getId() const;
    std::string getType() const;
    bool isAvailable() const;
    void setAvailable(bool status);
};
