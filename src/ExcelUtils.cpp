#include "ExcelUtils.hpp"
#include <xlnt/xlnt.hpp>
#include <vector>
#include <iostream>

void saveToFile(const std::vector<Customer> &customers, const std::string &filename)
{
    xlnt::workbook wb;
    auto ws = wb.active_sheet();
    ws.title("Customers");

    // Set headers
    ws.cell("A1").value("Username");
    ws.cell("B1").value("Password");
    ws.cell("C1").value("Name");
    ws.cell("D1").value("Gender");
    ws.cell("E1").value("Age");
    ws.cell("F1").value("Room");
    ws.cell("G1").value("Phone");

    int row = 2;
    for (const auto &c : customers)
    {
        ws.cell("A" + std::to_string(row)).value(c.getUsername());
        ws.cell("B" + std::to_string(row)).value(c.getPassword());
        ws.cell("C" + std::to_string(row)).value(c.getName());
        ws.cell("D" + std::to_string(row)).value(c.getGender());
        ws.cell("E" + std::to_string(row)).value(c.getAge());
        ws.cell("F" + std::to_string(row)).value(c.getRoom());
        ws.cell("G" + std::to_string(row)).value(c.getPhone());
        ++row;
    }

    wb.save(filename);
}

std::vector<Customer> loadFromFile(const std::string &filename)
{
    std::vector<Customer> customers;
    xlnt::workbook wb;

    // Handle file not found
    try
    {
        wb.load(filename);
    }
    catch (...)
    {
        return customers; // Return empty vector if file doesn't exist
    }

    auto ws = wb.active_sheet();
    int maxId = 0; // Track highest ID for counter

    for (auto row : ws.rows(false))
    {
        if (row[0].row() == 1) // Skip header row
            continue;

        try
        {
            std::string username = row[0].to_string();
            std::string password = row[1].to_string();
            std::string name = row[2].to_string();
            std::string gender = row[3].to_string();
            int age = row[4].value<int>();
            std::string room = row[5].to_string();
            std::string phone = row[6].to_string();

            customers.emplace_back(username, password, name, gender, age, phone, room);

            // Extract ID number to maintain counter
            std::string id = customers.back().getId();
            if (id.substr(0, 4) == "CUST")
            {
                int idNum = std::stoi(id.substr(4));
                maxId = std::max(maxId, idNum);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading customer row: " << e.what() << std::endl;
            continue; // Skip invalid rows
        }
    }

    // Set the ID counter to continue from the highest ID
    Customer::setIdCounter(maxId + 1);

    return customers;
}

void roomToFile(const std::vector<Room> &rooms, const std::string &filename)
{
    xlnt::workbook wb;
    auto ws = wb.active_sheet();
    ws.title("Rooms");

    // Set headers
    ws.cell("A1").value("Room ID");
    ws.cell("B1").value("Type");
    ws.cell("C1").value("Available");

    int row = 2;
    for (const auto &room : rooms)
    {
        ws.cell("A" + std::to_string(row)).value(room.getId());
        ws.cell("B" + std::to_string(row)).value(room.getType());
        ws.cell("C" + std::to_string(row)).value(room.isAvailable() ? "Yes" : "No");
        ++row;
    }

    wb.save(filename);
}

std::vector<Room> roomsFromFile(const std::string &filename)
{
    std::vector<Room> rooms;

    try
    {
        xlnt::workbook wb;
        wb.load(filename);
        auto ws = wb.active_sheet();

        for (auto row : ws.rows(false))
        {
            if (row[0].row() == 1) // Skip header row
                continue;

            try
            {
                std::string id = row[0].to_string();
                std::string type = row[1].to_string();
                bool available = row[2].to_string() == "Yes";

                rooms.emplace_back(id, type, available);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error loading room row: " << e.what() << std::endl;
                continue; // Skip invalid rows
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Could not load rooms file: " << e.what() << std::endl;
    }

    return rooms;
}