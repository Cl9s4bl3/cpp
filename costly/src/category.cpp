#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <tuple>

#include "include/json.hpp"
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

void categoryEntryManager(){

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
        std::cout << "\nAvailable actions:\n1) Create category\n2) Add to category\n3) Remove Category\n4) Exit" << std::endl;
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
                categoryEntryManager();
                break;

            case 3:
                removeCategory();
                break;

            case 4:
                std::cout << "\nExiting...\n" << std::endl;
                return;
        }
    }
}