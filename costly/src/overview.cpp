#include <iostream>
#include <fstream>

#include "headers/overview.h"
#include "include/json.hpp"


#define FILE "main.json"

using json = nlohmann::json;

void overView(){
    json data;

    std::ifstream inFile(FILE);

    if (!inFile){
        std::cout << "\nThere aren't any data yet.\n" << std::endl;
        return;
    }

    inFile >> data;
    inFile.close();

    std::cout << "\nCurrent balance: " << data["balance"] << "\n" << std::endl;

    std::cout << "All incomes:\n" << std::endl;

    if (data["income"].empty()){
        std::cout << "There are no income data yet." << std::endl;
    } else {
        for (auto& item : data["income"].items()){
            std::cout << "Name: " << item.key() << "; Value: " << item.value() << std::endl;
        }
    }


    std::cout << "\nAll expenses:\n" << std::endl;

    if (data["expense"].empty()){
        std::cout << "There are no expense data yet." << std::endl;
    } else {
        for (auto& item : data["expense"].items()){
            std::cout << "Name: " << item.key() << "; Value: " << item.value() << std::endl;
        }
    }

    std::cout << std::endl;
}