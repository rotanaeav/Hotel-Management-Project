#include "Room.hpp"

Room::Room(std::string id, std::string type, bool available)
    : id(id), type(type), available(available) {}

std::string Room::getId() const { return id; }
std::string Room::getType() const { return type; }
bool Room::isAvailable() const { return available; }
void Room::setAvailability(bool status) { available = status; }
