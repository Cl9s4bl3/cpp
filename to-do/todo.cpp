#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <limits>

using json = nlohmann::json;

void addTask() {
	std::string task_name;
	json data;

	std::cout << "Enter the name of the task: ";
	std::getline(std::cin, task_name);

	if (task_name.empty()) {
		std::cout << "\nTask name cannot be empty." << std::endl;
	}
	else {
		std::ifstream inFile("tasks.json");
		if (inFile.is_open()) {
			inFile >> data;
			inFile.close();
		}
		else {
			data = json::object();
		}

		data[task_name] = "false";

		std::ofstream outFile("tasks.json");
		outFile << data.dump(4);
		outFile.close();

		std::cout << "\nSuccessfully added \"" << task_name << "\" to to-do list." << std::endl;
	}
}

void listTasks() {
	json data;
	std::ifstream inFile("tasks.json");

	if (!inFile) {
		std::cout << "\nYou haven't added any tasks yet.\n";
		return;
	}

	inFile >> data;

	if (data.empty()) {
		std::cout << "\nYou haven't added any tasks yet.\n";
		return;
	}

	for (auto& [task, check] : data.items()) {

		std::string checked;

		if (check == "false") {
			checked = "No";
		}
		else {
			checked = "Yes";
		}

		std::cout << "\nTask name: " << task << "\nDone: " << checked << "\n" << std::endl;
	}
}

void removeTask() {
	std::string task_name;

	json data;
	std::ifstream inFile("tasks.json");

	if (!inFile) {
		std::cout << "\nYou haven't added any tasks yet.\n";
		return;
	}
	
	inFile >> data;

	if (data.empty()) {
		std::cout << "\nYou haven't added any tasks yet.\n";
		return;
	}

	std::cout << "\nAvailable tasks:\n" << std::endl;

	for (auto& [task, check] : data.items()) {
		std::cout << "- " << task << std::endl;
	}

	std::cout << "Enter the task you'd like to remove: ";
	std::getline(std::cin, task_name);

	if (!data.contains(task_name)) {
		std::cout << "\nThere is no task with the given name." << std::endl;
		return;
	}

	data.erase(task_name);

	std::ofstream outFile("tasks.json");

	outFile << data.dump(4);

	std::cout << "\nTask \"" << task_name << "\" was successfully deleted." << std::endl;
}






int main() {
	while (true) {
		int action;

		std::cout << "\nAvailable actions:\n1) Add task\n2) Remove task\n3) View all tasks\n4) Exit\n" << std::endl;
		std::cout << "Choose an action: ";
		std::cin >> action;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else {
			if (action == 1) {
				addTask();
			}
			else if (action == 2)
			{
				removeTask();
			}
			else if (action == 3)
			{
				listTasks();
			}
			else if (action == 4)
			{
				std::cout << "Exiting..." << std::endl;
				break;
			}
			else {
				std::cout << "\nInvalid action. Choose 1-4." << std::endl;
			}
		}
	}

	return 0;
}
