#include <iostream>
#include <fstream>

#include "include/json.hpp"
#include "headers/datamanager.h"

#define FILE "main.json"

using json = nlohmann::json;

void dataManager(){

    json data;
    std::ifstream inFile(FILE);

    if (!inFile){
        std::cout << "There are no data yet." << std::endl;
        return;
    }

    inFile >> data;
    inFile.close();


    while (true){
        int action;

        std::cout << "\nAvailable actions:\n1) Delete expense\n2) Delete income\n3) Change income data name\n4) Change expense data name\n5) Exit" << std::endl;
        std::cout << "\nChoose an action: ";
        std::cin >> action;

        if (std::cin.fail()){
            std::cout << "\nInvalid action!\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
}