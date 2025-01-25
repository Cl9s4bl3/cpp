#include <ios>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>

#include "include/json.hpp"
#include "headers/inex.h"

#define FILE "main.json"

using json = nlohmann::json;

void addIncome(){
    json data;

    std::string name;
    double value;
    double oldValue;

    std::ifstream inFile(FILE);

    if (!inFile){
        data = json::object();
    } else {
        inFile >> data;
    }

    inFile.close();

    std::cout << "Enter the name of the income: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    if (data["income"].contains(name)){
        std::cout << "\nThis entry already exists. Use Data manager to edit or delete the entry.\n" << std::endl;
        return;
    }


    std::cout << "Enter the value of the income: ";
    std::cin >> value;

    if (std::cin.fail()){
        std::cout << "\nInvalid amount!\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    oldValue = data["balance"];

    data["income"][name] = value;
    data["balance"] = oldValue + value;

    std::ofstream outFile(FILE);
    outFile << data.dump(4);
    outFile.close();

    std::cout << "\nSuccessfully added income '" << name << "'\n" << std::endl;

}

void addExpense(){
    json data;

    std::string name;
    double value;
    double oldValue;

    std::ifstream inFile(FILE);

    if (!inFile){
        data = json::object();
    } else {
        inFile >> data;
    }

    inFile.close();

    std::cout << "Enter the name of the expense: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    if (data["expense"].contains(name)){
        std::cout << "\nThis entry already exists. Use Data manager to edit or delete the entry.\n" << std::endl;
        return;
    }


    std::cout << "Enter the value of the expense: ";
    std::cin >> value;

    if (std::cin.fail()){
        std::cout << "\nInvalid amount!\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    oldValue = data["balance"];

    data["expense"][name] = value;
    data["balance"] = oldValue - value;

    std::ofstream outFile(FILE);
    outFile << data.dump(4);
    outFile.close();

    std::cout << "\nSuccessfully added expense '" << name << "'\n" << std::endl;
}