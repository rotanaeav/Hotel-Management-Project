#include "Input.hpp"
#include <iostream>
#include <tabulate/table.hpp>
#include "color.hpp"
using namespace tabulate;
Customer input()
{
    system("cls");

    std::cout<<YELLOW<<" ____  _____ ____ ___ ____ _____ _____ ____       _    ____ ____ ___  _   _ _   _ _____ "<<std::endl;
    std::cout<<"|  _ \\| ____/ ___|_ _/ ___|_   _| ____|  _ \\     / \\  / ___/ ___/ _ \\| | | | \\ | |_   _|"<<std::endl;
    std::cout<<"| |_) |  _|| |  _ | |\\___ \\ | | |  _| | |_) |   / _ \\| |  | |  | | | | | | |  \\| | | |  "<<std::endl;
    std::cout<<"|  _ <| |__| |_| || | ___) || | | |___|  _ <   / ___ \\ |__| |__| |_| | |_| | |\\  | | |  "<<std::endl;
    std::cout<<"|_| \\_\\_____\\____|___|____/ |_| |_____|_| \\_\\ /_/   \\_\\____\\____\\___/ \\___/|_| \\_| |_|  "<<std::endl;
    std::cout<<RESET<<std::endl;

    std::string username, password, name, gender, phone;
    int age;

    std::cout << YELLOW << "Enter Username: "<<RESET;
    std::cin >> username;
    std::cout << YELLOW << "Enter Password: "<<RESET;
    std::cin >> password;
    std::cout << YELLOW << "Enter Name: "<<RESET;
    std::cin >> name;
    std::cout << YELLOW << "Enter Gender: "<<RESET;
    std::cin >> gender;
    std::cout << YELLOW << "Enter Age: "<<RESET;
    std::cin >> age;
    std::cout << YELLOW << "Enter Phone: "<<RESET;
    std::cin >> phone;
    return Customer(username, password, name, gender, age, phone);
}