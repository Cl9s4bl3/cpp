#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#define FILE "banking.json"
#define CURRENCY "$"


void static checkBalance(std::string username) {
	json data;
	double balance;

	std::ifstream inFile(FILE);

	if (inFile.peek() == std::ifstream::traits_type::eof()) {
		data = json::object();
	}
	else {
		inFile >> data;
	}

	inFile.close();

	balance = data["balance"][username];

	std::cout << "\nCurrent balance: " << balance << "" << CURRENCY << std::endl;
}


void static loggedIn(std::string username, std::string password) {
	while (true) {

		int action;

		std::cout << "\nAvailable actions:\n1) Check balance\n2) Logout" << std::endl;

		std::cout << "\nChoose an action: ";
		std::cin >> action;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (std::cin.fail()) {
			std::cout << "\nInvalid number!" << std::endl;
			std::cin.clear();
		}
		else {
			switch (action)
			{
				case 1:
					checkBalance(username);
					break;

				case 2:
					std::cout << "\nLogging out..." << std::endl;
					return;
			
				default:
					std::cout << "\nInvalid action. Choose 1-3" << std::endl;
					break;
			}
		}


	}
}



void static login() {
	json data;
	std::string username, password;

	std::ifstream inFile(FILE);

	if (inFile.peek() == std::ifstream::traits_type::eof()) {
		std::cout << "\nNo-one has registered yet" << std::endl;
		return;
	}
	else {
		inFile >> data;
	}

	if (data.size() <= 1) {
		std::cout << "\nNo-one has registered yet" << std::endl;
		return;
	}

	inFile.close();

	while (true) {
		std::cout << "\nEnter your username: ";
		std::getline(std::cin, username);

		if (username.empty()) {
			std::cout << "\nUsername cannot be blank" << std::endl;
			continue;
		}

		std::cout << "Enter your password: ";
		std::getline(std::cin, password);

		if (password.empty()) {
			std::cout << "\nPassword cannot be blank" << std::endl;
			continue;
		}

		break;
	}

	if (data["users"][username] == password) {
		std::cout << "\nLogin successful!" << std::endl;
		loggedIn(username, password);
	}
	else {
		std::cout << "\nInvalid username or password!" << std::endl;
	}
}

void static registration() {
	json data;
	std::string username, password;

	std::ifstream inFile(FILE);

	if (inFile.peek() == std::ifstream::traits_type::eof()) {
		data = json::object();
	}
	else {
		inFile >> data;
	}

	inFile.close();

	while (true) {
		std::cout << "\nEnter your username: ";
		std::getline(std::cin, username);

		if (username.empty()) {
			std::cout << "\nUsername cannot be blank" << std::endl;
			continue;
		}

		if (data["users"].contains(username)) {
			std::cout << "\nUsername already exist\n";
			continue;
		}

		std::cout << "Enter your password: ";
		std::getline(std::cin, password);

		if (password.empty()) {
			std::cout << "\nPassword cannot be blank" << std::endl;
			continue;
		}

		break;
	}
					
	data["users"][username] = password;
	data["balance"][username] = 0;

	std::ofstream outFile(FILE);
	outFile << data.dump(4);
	outFile.close();

	std::cout << "\nSuccessfully created account!" << std::endl;
}

int main() {
	while (true) {
		int action;

		std::cout << "\nLogin into your account or create one\n1) Login\n2) Register\n3) Exit" << std::endl;

		std::cout << "\nChoose an action: ";
		
		std::cin >> action;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (std::cin.fail()) {
			std::cout << "\nInvalid number!" << std::endl;
			std::cin.clear();
		}
		else {
			switch (action)
			{
				case 1:
					login();
					break;

				case 2:
					registration();
					break;

				case 3:
					std::cout << "\nExiting..." << std::endl;
					return 0;

				default:
					std::cout << "\nInvalid action. Choose 1-3" << std::endl;
					break;
			}
		}
	}
	
	return 0;
}