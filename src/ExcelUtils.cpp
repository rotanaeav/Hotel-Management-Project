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

    try
    {
        wb.load(filename);
    }
    catch (...)
    {
        return customers; // file might not exist yet
    }

    auto ws = wb.active_sheet();
    for (auto row : ws.rows(false))
    {
        if (row[0].row() == 1)
            continue; // skip header

        std::string name = row[0].to_string();
        std::string gender = row[1].to_string();
        int age = row[2].value<int>();
        std::string room = row[3].to_string();
        std::string phone = row[4].to_string();

        customers.emplace_back(name, gender, age, room, phone);
    }

    return customers;
}
