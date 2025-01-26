#include <cmath>
#include <iostream>
#include <fstream>
#include <list>
#include <ratio>
#include <string>
#include <utility>

#include "include/json.hpp"
#include "headers/datamanager.h"

#define FILE "main.json"

using json = nlohmann::json;

void writeFile(json data){
    std::ofstream outFile(FILE);
    outFile << data.dump(4);
    outFile.close();
}

void deleteData(json data, std::string table, std::string data_name){
    data[table].erase(data_name);
    writeFile(data);

    std::cout << "\nSuccessfully deleted '" << data_name << "'." << std::endl;
}

void changeDataName(json &data, const std::string &table, const std::string &data_name) {
    std::string new_name;
    std::string new_value;
    double new_value_double = 0.0;
    double value = 0.0;

    std::cout << "\nEnter new name for '" << data_name << "': ";
    std::getline(std::cin, new_name);

    std::cout << "Enter new value for '" << new_name << "' (type default for keeping the original value): ";
    std::getline(std::cin, new_value);

    if (new_value == "default") {
        value = data[table][data_name].get<double>();
    } else {
        try {
            new_value_double = std::stod(new_value);
        } catch (const std::invalid_argument &) {
            std::cerr << "Error: Invalid input. New value must be a number or 'default'.\n";
            return;
        }

        double old_entry_balance = data[table][data_name].get<double>();
        double balance_change = new_value_double - old_entry_balance;

        data["balance"] = data["balance"].get<double>() + balance_change;

        value = new_value_double;
    }

    data[table].erase(data_name);
    data[table][new_name] = value;

    writeFile(data);

    std::cout << "\nSuccessfully saved changes." << std::endl;
}

void incomeData(json data){
    int entry;

    std::vector<std::pair<int, std::string>> table_data;

    if (!data.contains("income") || data["income"].empty()){
        std::cout << "\nThere are no income data yet." << std::endl;
        return;
    }

    std::cout << std::endl;

    int index = 1;
    for (auto& [key, value] : data["income"].items()) {
        table_data.push_back(std::make_pair(index, key));
        index++;
    }

    for (const auto& [index, name] : table_data) {
        std::cout << index << ") " << name << std::endl;
    }

    std::cout << "\nChoose an entry to modify: ";
    std::cin >> entry;

    if (std::cin.fail()){
            std::cout << "\nInvalid entry!\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        bool found = false;
        std::string data_name;
        for (auto& [index, name] : table_data){
            if (index == entry){
                found = true;
                data_name = name;
            }
        }

        if (!found){
            std::cout << "There's no entry with number " << entry << std::endl;
        }

        std::cout << "\nYou've selected " << data_name << "." << std::endl;

        int decision;

        std::cout << "\nAvailable actions:\n1) Edit name and value\n2) Delete entry\n3) Exit" << std::endl;
        std::cout << "\nChoose an action: ";
        std::cin >> decision;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::cin.fail()){
            std::cout << "\nInvalid action!\n" << std::endl;
            std::cin.clear();
        } else {
            switch (decision) {
                case 1:
                    changeDataName(data, "income", data_name);
                    break;

                case 2:
                    deleteData(data, "income", data_name);
                    break;
                case 3:
                    std::cout << "\nExiting...\n" << std::endl;
                    break;

                default:
                    std::cout << "\nInvalid action!\n" << std::endl;
            }
        }
    }
}

void expenseData(json data){
    int entry;

    std::vector<std::pair<int, std::string>> table_data;

    if (!data.contains("expense") || data["expense"].empty()){
        std::cout << "\nThere are no expense data yet." << std::endl;
        return;
    }

    std::cout << std::endl;

    int index = 1;
    for (auto& [key, value] : data["expense"].items()) {
        table_data.push_back(std::make_pair(index, key));
        index++;
    }

    for (const auto& [index, name] : table_data) {
        std::cout << index << ") " << name << std::endl;
    }

    std::cout << "\nChoose an entry to modify: ";
    std::cin >> entry;

    if (std::cin.fail()){
            std::cout << "\nInvalid entry!\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        bool found = false;
        std::string data_name;
        for (auto& [index, name] : table_data){
            if (index == entry){
                found = true;
                data_name = name;
            }
        }

        if (!found){
            std::cout << "There's no entry with number " << entry << std::endl;
        }

        std::cout << "\nYou've selected " << data_name << "." << std::endl;

        int decision;

        std::cout << "\nAvailable actions:\n1) Edit name and value\n2) Delete entry\n3) Exit" << std::endl;
        std::cout << "\nChoose an action: ";
        std::cin >> decision;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::cin.fail()){
            std::cout << "\nInvalid action!\n" << std::endl;
            std::cin.clear();
        } else {
            switch (decision) {
                case 1:
                    changeDataName(data, "expense", data_name);
                    break;

                case 2:
                    deleteData(data, "expense", data_name);
                    break;
                case 3:
                    std::cout << "\nExiting...\n" << std::endl;
                    break;

                default:
                    std::cout << "\nInvalid action!\n" << std::endl;
            }
        }
    }
}

void dataManager(){
    json data;


    while (true){
        int action;

        std::ifstream inFile(FILE);

        if (!inFile){
            std::cout << "There's no data yet." << std::endl;
            return;
        }

        inFile >> data;
        inFile.close();

        std::cout << "\nAvailable actions:\n1) Modify income data table\n2) Modify expense data table\n3) Exit" << std::endl;
        std::cout << "\nChoose an action: ";
        std::cin >> action;

        if (std::cin.fail()){
            std::cout << "\nInvalid action!\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (action) {
            case 1:
                incomeData(data);
                break;

            case 2:
                expenseData(data);
                break;

            case 3:
                std::cout << "\nExiting...\n" << std::endl;
                return;

        }
    }
}