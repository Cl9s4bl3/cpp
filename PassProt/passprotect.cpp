#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool static jsonEmpty(const json& data) {
    return data.is_object() && data.empty();
}

std::string static generateRandomString(int length) {
    std::string characters = "A@BCDEFGHIJKLMNOPQR0123-456789STU(VWXYZabcdefghij!klmnopqrstuvwx)yz";
    std::string randomString;

    for (int i = 0; i < length; i++) {
        randomString += characters[rand() % characters.size()];
    }

    return randomString;
}

void static ownPass() {
    json data;

    std::string passName;
    std::string master;
    std::string choice;
    std::string ownPass;

    std::cout << "\nEnter your password: ";
    std::getline(std::cin, ownPass);

    while (true) {
        while (true) {
            std::cout << "Enter password's name: ";
            std::getline(std::cin, passName);
            if (passName.empty()){
                std::cout << "\nPassword's name cannot be blank." << std::endl;
                continue;
            }

            if (passName != "master") {
                break; 
            } else {
                std::cout << "\nPassword name cannot be \"master\".\n"; 
            }
        }

        std::ifstream inFile("passwords.json");

        if (inFile.is_open()) {

            if (inFile.peek() == std::ifstream::traits_type::eof()) {
                data = json::object();
            }
            else {
                inFile >> data;
            }

            inFile.close();
        }
        else {
            data = json::object();
        }

        if (data.contains(passName)) {
            std::cout << "\nA password with this name already exists." << std::endl;
        }
        else {
            break;
        }
    }

    if (!data.contains("master") && jsonEmpty(data)) {
        std::cout << "Enter a master password: ";
        std::getline(std::cin, master);

        data["master"] = master;
    }

    data[passName] = ownPass;

    std::ofstream outFile("passwords.json");

    outFile << data.dump(4);
    outFile.close();

    std::cout << "\nAlready existing password for \"" << passName << "\" was successfully added." << std::endl;

}

void static changeMaster() {
    json data;

    std::string oldPass;
    std::string newPass;

    std::ifstream inFile("passwords.json");

    if (!inFile.is_open()) {
        std::cout << "\nYou don't have a master password yet." << std::endl;
        return;
    }

    if (inFile.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "\nYou don't have a master password yet." << std::endl;
        return;
    }

    inFile >> data;


    if (!data.contains("master")) {
        std::cout << "\nYou don't have a master password yet." << std::endl;
        return;
    }

    std::cout << "Enter your old password: ";
    std::getline(std::cin, oldPass);

    if (data["master"] != oldPass) {
        std::cout << "\nInvalid old master password." << std::endl;
        return;
    }

    std::cout << "\nEnter the new master password: ";
    std::getline(std::cin, newPass);

    data["master"] = newPass;

    std::ofstream outFile("passwords.json");
    outFile << data.dump(4);

    std::cout << "\nSuccessfully changed master password" << std::endl;
    inFile.close();
    outFile.close();
}

void static listPasswords() {
    try {
        json data;
        std::string master;

        std::ifstream inFile("passwords.json");

        if (!inFile) {
            std::cout << "\nNo passwords have been added yet." << std::endl;
            return;
        }

        inFile >> data;

        if (data.size() <= 1) {
            std::cout << "\nNo passwords have been added yet." << std::endl;
            return;
        }

        std::cout << "\nEnter master password: ";
        std::getline(std::cin, master);

        if (data["master"] == master) {
            std::cout << "\nSaved passwords:\n" << std::endl;
            for (auto& [name, pass] : data.items()) {
                if (name == "master") {
                    continue;
                }
                std::cout << "- " << name << ": " << pass << std::endl;
            }
        }
        else {
            std::cout << "\nInvalid master password." << std::endl;
        }
        inFile.close();
    }
    catch (json::exception e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
}

void static removePassword() {
    json data;

    std::string pass_name;
    std::string master;

    std::ifstream inFile("passwords.json");

    if (!inFile) {
        std::cout << "\nNo passwords have been added yet." << std::endl;
        return;
    }

    inFile >> data;

    if (jsonEmpty(data)) {
        std::cout << "\nNo passwords have been added yet." << std::endl;
        return;
    }

    std::cout << "\nEnter master password: ";
    std::getline(std::cin, master);

    if (data["master"] == master) {
        if (data.size() == 1) {
            std::cout << "\nNo passwords have been added yet." << std::endl;
            return;
        }
        std::cout << "\nSaved passwords:\n" << std::endl;
        for (auto& [name, pass] : data.items()) {
            if (name == "master") {
                continue;
            }
            std::cout << "- " << name << ": " << pass << std::endl;
        }
    }
    else {
        std::cout << "\nInvalid master password." << std::endl;
        return;
    }





    std::cout << "\nEnter the name of the password you'd like to delete: ";
    std::getline(std::cin, pass_name);

    if (!data.contains(pass_name)) {
        std::cout << "\nPassword \"" << pass_name << " \"does not exist." << std::endl;
        return;
    }

    data.erase(pass_name);

    std::ofstream outFile("passwords.json");
    outFile << data.dump(4);

    std::cout << "\nPassword \"" << pass_name << "\" was successfully deleted." << std::endl;
    inFile.close();
    outFile.close();
}

void static addPassword() {
    json data;
    int length = 8;

    std::string passName;
    std::string master;
    std::string choice;
    std::string randomPass;

    srand(static_cast<unsigned int>(time(0)));

    std::cout << "\nEnter the password's length: ";
    std::cin >> length;
    std::cin.ignore();

    if (std::cin.fail()) {
        std::cout << "\nInvalid number." << std::endl;
        std::cin.clear();
        std::cin.ignore();
        return;
    }

    randomPass = generateRandomString(length);
    std::cout << "Your randomly created password is: " << randomPass << std::endl;
    std::cout << "\nWould you like to save this password (yes/no)? ";
    std::getline(std::cin, choice);

    if (choice != "yes") {
        std::cout << "\nContinuing without saving password.\n";
        return;
    }

    while (true) {
        while (true) {
            std::cout << "\nEnter password's name: ";
            std::getline(std::cin, passName);
            if (passName.empty()) { std::cout << "\nPassword's name cannot be blank." << std::endl; continue; }
            if (passName != "master") { break; }
            else { std::cout << "\nPassword name cannot be \"master\".\n"; }
        }

        std::ifstream inFile("passwords.json");

        if (inFile.is_open()) {

            if (inFile.peek() == std::ifstream::traits_type::eof()) {
                data = json::object();
            }
            else {
                inFile >> data;
            }

            inFile.close();
        }
        else {
            data = json::object();
        }

        if (data.contains(passName)) {
            std::cout << "\nA password with this name already exists." << std::endl;
        }
        else {
            break;
        }
    }

    if (!data.contains("master") && jsonEmpty(data)) {
        std::cout << "Enter a master password: ";
        std::getline(std::cin, master);

        data["master"] = master;
    }

    data[passName] = randomPass;

    std::ofstream outFile("passwords.json");

    outFile << data.dump(4);
    outFile.close();

    std::cout << "\nPassword for \"" << passName << "\" was successfully added." << std::endl;
}


int main() {
    while (true) {
        int action;

        std::cout << "\nAvailable actions:\n1) Generate password\n2) Add existing password\n3) List all passwords\n4) Delete password\n5) Change master password\n6) Exit" << std::endl;

        std::cout << "\nChoose an action: ";

        std::cin >> action;
        std::cin.ignore();

        if (std::cin.fail()) {
            std::cout << "Invalid number." << std::endl;
            std::cin.clear();
            std::cin.ignore();
        }
        else {
            switch (action)
            {
            case 1:
                addPassword();
                break;

            case 2:
                ownPass();
                break;

            case 3:
                listPasswords();
                break;

            case 4:
                removePassword();
                break;

            case 5:
                changeMaster();
                break;

            case 6:
                return 0;

            default:
                std::cout << "Invalid action. Choose 1-6" << std::endl;
                break;
            }
        }
    }
    return 0;
}
