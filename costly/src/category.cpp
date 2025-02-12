#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <tuple>

#include "include/json.hpp"
#include "headers/overview.h"
#include "headers/category.h"

#define FILE "main.json"

using json = nlohmann::json;

void createCategory(){
    json data;
    std::ifstream inFile(FILE);

    inFile >> data;
    inFile.close();

    std::string cat_name;
    std::cout << "\nEnter a name for the category: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, cat_name);

    if (data["categories"].contains(cat_name)){
        std::cout << "Category name already exists." << std::endl;
        return;
    } else {
        data["categories"][cat_name] = json::object();
    }

    std::cout << "\nSuccessfully created category '" << cat_name << "'." << std::endl;

    std::ofstream outFile(FILE);
    outFile << data.dump(4);
    outFile.close();
}

void addToCategory(){
    json data;

    std::string entry_name;
    std::string cat_name;

    overView();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nEnter the name of the entry: ";
    std::getline(std::cin, entry_name);

    std::cout << "\nEnter the name of the category: ";
    std::getline(std::cin, cat_name);

    std::ifstream inFile(FILE);
    inFile >> data;
    inFile.close();

    if (!(data["expense"].contains(entry_name) || data["income"].contains(entry_name))){
        std::cout << "\nThis entry does not exist." << std::endl;
        return;
    } else {
        if (!data["categories"].contains(cat_name)){
            std::cout << "\nThe specified category does not exist." << std::endl;
            return;
        } else {
            data["categories"][cat_name][entry_name] = {};
            std::cout << "\nSuccessfully added '" << entry_name << "' to category '" << cat_name << "'." << std::endl;
        }
    }

    std::ofstream outFile(FILE);
    outFile << data.dump(4);
    outFile.close();
}

void removeFromCategory(){
    json data;

    std::string entry_name;
    std::string cat_name;

    overView();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nEnter the name of the entry: ";
    std::getline(std::cin, entry_name);

    std::cout << "\nEnter the name of the category: ";
    std::getline(std::cin, cat_name);

    std::ifstream inFile(FILE);
    inFile >> data;
    inFile.close();

    if (!(data["expense"].contains(entry_name) || data["income"].contains(entry_name))){
        std::cout << "\nThis entry does not exist." << std::endl;
        return;
    } else {
        if (!data["categories"].contains(cat_name)){
            std::cout << "\nThe specified category does not exist." << std::endl;
            return;
        } else {
            data["categories"][cat_name].erase(entry_name);
            std::cout << "\nSuccessfully deleted '" << entry_name << "' from category '" << cat_name << "'." << std::endl;
        }
    }

    std::ofstream outFile(FILE);
    outFile << data.dump(4);
    outFile.close();
}

void categoryEntryManager(){
    int action;
    std::cout << "\nAvailable actions:\n1) Add item to a category\n2) Remove item from a category\n3) Exit" << std::endl;
    std::cout << "\nChoose an action: ";
    std::cin >> action;

    if (std::cin.fail()){
        if (std::cin.fail()){
            std::cout << "\nInvalid action!\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } else {
        switch (action) {
            case 1:
                addToCategory();
                break;

            case 2:
                removeFromCategory();
                break;
            case 3:
                return;

            default:
                std::cout << "Invalid action." << std::endl;
        }
    }

}

void removeCategory(){
    json data;
    std::ifstream inFile(FILE);

    inFile >> data;
    inFile.close();

    std::string cat_name;
    std::cout << "\nEnter the name of the category: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, cat_name);

    if (data["categories"].contains(cat_name)){
        data["categories"].erase(cat_name);
    } else {
        std::cout << "\nNo such category." << std::endl;
        return;
    }

    std::cout << "\nSuccessfully delete category '" << cat_name << "'." << std::endl;

    std::ofstream outFile(FILE);
    outFile << data.dump(4);
    outFile.close();
}

void categoryManager(){


    while (true){
        int action;
        std::cout << "\nAvailable actions:\n1) Create category\n2) Remove Category\n3) Add to or remove from category\n4) Exit" << std::endl;
        std::cout << "\nChoose an action: ";
        std::cin >> action;

        if (std::cin.fail()){
            std::cout << "\nInvalid action!\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (action) {
            case 1:
                createCategory();
                break;

            case 2:
                removeCategory();
                break;

            case 3:
                categoryEntryManager();
                break;

            case 4:
                std::cout << "\nExiting...\n" << std::endl;
                return;
        }
    }
}