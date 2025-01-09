#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#define FILE "banking.json"
#define CURRENCY "$"


void static transfer(std::string username) {
	json data;

	std::string to;
	float amount;

	float senderBalance;
	float receiverBalance;

	float senderRemaining;
	float receiverRemaining;

	std::ifstream inFile(FILE);

	if (!inFile) {
		std::cout << "\nAccount doesn't exist." << std::endl;
		return;
	}

	if (inFile.peek() == std::ifstream::traits_type::eof()) {
		std::cout << "\nAccount doesn't exist." << std::endl;
		return;
	}
	else {
		inFile >> data;
	}

	inFile.close();

	while (true) {
		std::cout << "\nEnter the name of the recepient: ";
		std::getline(std::cin, to);

		if (to.empty()) {
			std::cout << "\nUsername cannot be empty!" << std::endl;
			continue;
		}

		if (!data["users"].contains(to) || to == username) {
			std::cout << "\nUsername is invalid." << std::endl;
			continue;
		}

		std::cout << "Enter the amount: ";
		std::cin >> amount;

		

		if (std::cin.fail()) {
			std::cout << "\nInvalid number!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (amount <= 0) {
			std::cout << "\nAmount cannot be zero or lower." << std::endl;
			continue;
		}

		break;
	}

	senderBalance = data["balance"][username];

	if (amount > senderBalance) {
		std::cout << "\nNot enough money on the sender's balance." << std::endl;
		return;
	}

	receiverBalance = data["balance"][to];

	senderRemaining = std::round((senderBalance - amount) * 100.0) / 100.0;
	receiverRemaining = amount + receiverBalance;

	data["balance"][username] = senderRemaining;
	data["balance"][to] = receiverRemaining;

	std::ofstream outFile(FILE);
	outFile << data.dump(4);

	std::cout << "\nYou've successfully sent " << to << " " << amount << CURRENCY << std::endl;
	outFile.close();
}


void static deposit(std::string username) {
	json data;
	float deposit;
	float balance;
	float remaining;

	std::ifstream inFile(FILE);

	if (!inFile) {
		std::cout << "\nAccount doesn't exist." << std::endl;
		return;
	}

	if (inFile.peek() == std::ifstream::traits_type::eof()) {
		std::cout << "\nAccount doesn't exist." << std::endl;
		return;
	}
	else {
		inFile >> data;
	}

	inFile.close();

	while (true) {
		std::cout << "\nEnter the amount you want to deposit: ";
		std::cin >> deposit;

		if (std::cin.fail()) {
			std::cout << "\nInvalid number!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (deposit <= 0) {
			std::cout << "\nAmount cannot be zero or lower." << std::endl;
			continue;
		}
		
		break;
	}


	balance = data["balance"][username];

	remaining = balance + deposit;

	data["balance"][username] = remaining;

	std::ofstream outFile(FILE);
	outFile << data.dump(4);

	std::cout << "\nSuccessfully deposited " << deposit << CURRENCY << std::endl;
	outFile.close();
}


void static withdraw(std::string username) {
	json data;
	float withdraw;
	float balance;
	float remaining;

	std::ifstream inFile(FILE);

	if (!inFile) {
		std::cout << "\nAccount doesn't exist." << std::endl;
		return;
	}

	if (inFile.peek() == std::ifstream::traits_type::eof()) {
		std::cout << "\nAccount doesn't exist." << std::endl;
		return;
	}
	else {
		inFile >> data;
	}

	inFile.close();

	while (true) {

		std::cout << "\nEnter the amount you want to withdraw: ";
		std::cin >> withdraw;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (std::cin.fail()) {
			std::cout << "\nInvalid number!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (withdraw <= 0) {
			std::cout << "\nAmount cannot be zero or lower." << std::endl;
			continue;
		}

		break;
	}

	balance = data["balance"][username];

	if (withdraw > balance) {
		std::cout << "\nNot enough money." << std::endl;
		return;
	}
	else {
		remaining = std::round((balance - withdraw) * 100.0) / 100.0;
	}

	data["balance"][username] = remaining;

	std::ofstream outFile(FILE);
	outFile << data.dump(4);

	std::cout << "\nSuccessfully withdrawed " << withdraw << CURRENCY << std::endl;
	outFile.close();
}

void static checkBalance(std::string username) {
	json data;
	float balance;

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

	return;
}


void static loggedIn(std::string username, std::string password) {
	while (true) {

		int action;

		std::cout << "\nAvailable actions:\n1) Check balance\n2) Withdraw from balance\n3) Deposit into balance\n4) Transfer\n5) Logout" << std::endl;

		std::cout << "\nChoose an action: ";
		std::cin >> action;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (std::cin.fail()) {
			std::cout << "\nInvalid number!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			switch (action)
			{
				case 1:
					checkBalance(username);
					break;

				case 2:
					withdraw(username);
					break;

				case 3:
					deposit(username);
					break;

				case 4:
					transfer(username);
					break;

				case 5:
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
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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