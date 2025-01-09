// Sort-it: A JSON stores the places the sorted files should be placed and when you start the sorting, it asks you which
// folder you'd like to sort

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#define FILE "settings.json"


void static settings() {
	std::cout << "Settings" << std::endl;
}

void static sort() {
	std::cout << "Sort" << std::endl;
}


int main() {
	json data;

	std::ifstream inFile(FILE);

	if (!inFile || inFile.peek() == std::ifstream::traits_type::eof()) {
		data = {
			{"videos", "notset"},
			{"text", "notset"}
		};
	}
	else {
		inFile >> data;

		if (data.size() < 2) {
			data = {
			{"videos", "notset"},
			{"text", "notset"}
			};
		}
	}

	inFile.close();

	std::ofstream outFile(FILE);

	outFile << data.dump(4);
	outFile.close();

	while (true) {
		int action;

		std::cout << "\nAvailable actions:\n1) Settings\n2) Sort it" << std::endl;
		std::cout << "\nChoose an action: ";
		std::cin >> action;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (std::cin.fail()) {
			std::cout << "Invalid number." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			switch (action)
			{
				case 1:
					settings();
					break;

				case 2:
					sort();
					break;

				default:
					std::cout << "Invalid choice. Choose 1-2" << std::endl;
					break;
			}
		}
	}

	return 0;
}