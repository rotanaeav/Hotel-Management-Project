#include "ExcelUtils.hpp"
#include <xlnt/xlnt.hpp>
#include <vector>

void saveToFile(const std::vector<Customer> &customers, const std::string &filename)
{
    xlnt::workbook wb;
    auto ws = wb.active_sheet();
    ws.title("Customers");

    ws.cell("A1").value("Name");
    ws.cell("B1").value("Gender");
    ws.cell("C1").value("Age");
    ws.cell("D1").value("Room");
    ws.cell("E1").value("Phone");

    int row = 2;
    for (const auto &c : customers)
    {
        ws.cell("A" + std::to_string(row)).value(c.getName());
        ws.cell("B" + std::to_string(row)).value(c.getGender());
        ws.cell("C" + std::to_string(row)).value(c.getAge());
        ws.cell("D" + std::to_string(row)).value(c.getRoom());
        ws.cell("E" + std::to_string(row)).value(c.getPhone());
        ++row;
    }

    wb.save(filename);
}

std::vector<Customer> loadFromFile(const std::string &filename)
{
    std::vector<Customer> customers;
    xlnt::workbook wb;
    // crash handle
    try
    {
        wb.load(filename);
    }
    catch (...)
    {
        return customers;
    }

    auto ws = wb.active_sheet();
    for (auto row : ws.rows(false))
    {
        if (row[0].row() == 1)
            continue;

        std::string name = row[0].to_string();
        std::string gender = row[1].to_string();
        int age = row[2].value<int>();
        std::string room = row[3].to_string();
        std::string phone = row[4].to_string();

        customers.emplace_back(name, gender, age, room, phone);
    }

    return customers;
}
void roomToFile(const std::vector<Room> &rooms, const std::string &filename)
{
    xlnt::workbook wb;
    auto ws = wb.active_sheet();
    ws.title("Rooms");
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
            if (row[0].row() == 1)
                continue;

            std::string id = row[0].to_string();
            std::string type = row[1].to_string();
            bool available = row[2].to_string() == "Yes";

            rooms.emplace_back(id, type, available);
        }
    }
    // handle crash
    catch (const std::exception &e)
    {
        std::cout << "Hotel Closed" << e.what() << std::endl;
    }

    return rooms;
}