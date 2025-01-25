#include <iostream>
#include <fstream>
#include <string>

#include "include/json.hpp"
#include "headers/inex.h"
#include "headers/overview.h"
#include "headers/category.h"
#include "headers/datamanager.h"

#define FILE "main.json"

using json = nlohmann::json;

void createJSON(){
    json data;

    std::ifstream inFile(FILE);

    if (!inFile){
        data = json::object();
    } else {
        inFile >> data;
    }

    inFile.close();

    if (!data.contains("balance")){
        data["balance"] = 0.0;
    }

    std::ofstream outFile(FILE);
    outFile << data.dump(4);
    outFile.close();
}

int main(){

    createJSON();

    while (true){
        int action;

        std::cout << "Available actions:\n1) Add expense\n2) Add income\n3) Data manager\n4) Overview\n5) Category manager\n6) Exit" << std::endl;

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
                addExpense();
                break;

            case 2:
                addIncome();
                break;

            case 3:
                dataManager();
                break;

            case 4:
                overView();
                break;

            case 5:
                categoryManager();
                break;

            case 6:
                std::cout << "Exiting..." << std::endl;
                return 0;

            default:
                std::cout << "\nInvalid action!\n" << std::endl;
                break;

        }
    }

    return 0;
}
