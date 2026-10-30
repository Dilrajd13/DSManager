#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <cctype>

#include "DataStructure.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "Heap.h"
#include "BinaryTree.h"

//every created data structure, looked up by its name
std::map<std::string, std::unique_ptr<DataStructure>> structures;

//command list
std::vector<std::string> cmds = { "help","dsls","new","view","add","remove","search","edit","rm","exit" };

std::string toLower(std::string text) {
	std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) { return (char)std::tolower(c); });
	return text;
}

//Prints text for startup, errors, etc..
void displayHandler(int x) {

	//Startup Text = 1
	if (x == 1) {
		std::cout << "Data Structure Manager V1 \n\n";
		std::cout << "Welcome to DS Manager, a Terminal to create, visualize and edit Data Structures.\n";
		std::cout << "Type help to see the list of commands.\n\n";
	}
	//Unknown command = 2
	if (x == 2) {
		std::cout << "Unknown command. Type help to see the list of commands.\n";
	}
	//Wrong arguments = 3
	if (x == 3) {
		std::cout << "Wrong arguments for that command. Type help to see how to use it.\n";
	}
}

// Finds a data structure by name, prints an error and returns NULL if it doesn't exist
DataStructure* findStructure(std::string name) {
	auto found = structures.find(name);
	if (found == structures.end()) {
		std::cout << "No data structure called " << name << ". Type DSLS to see what exists.\n";
		return NULL;
	}
	return found->second.get();
}

// Makes the data structure matching the type the user typed, returns NULL if the type isn't real
std::unique_ptr<DataStructure> createStructure(std::string type) {
	type = toLower(type);
	if (type == "ll" || type == "linkedlist") return std::make_unique<LinkedList>();
	if (type == "stack") return std::make_unique<Stack>();
	if (type == "queue") return std::make_unique<Queue>();
	if (type == "heap") return std::make_unique<Heap>();
	if (type == "tree" || type == "binarytree") return std::make_unique<BinaryTree>();
	return NULL;
}

//COMMAND Functions

// help - prints list of commands and description from help.txt
void helpCommand() {
	std::ifstream helpFile("help.txt");
	if (!helpFile) {
		std::cout << "help.txt wasn't found, run DSManager from the project folder. Commands:\n";
		for (int i = 0; i < cmds.size(); i++) {
			std::cout << "  " << cmds[i] << "\n";
		}
		return;
	}
	std::cout << helpFile.rdbuf();
}

// DSLS - lists all created objects (like ls )
void dslsCommand() {
	if (structures.empty()) {
		std::cout << "No data structures yet. Make one with new.\n";
		return;
	}
	for (auto& entry : structures) {
		std::cout << entry.first << "  (" << entry.second->typeName() << ", size " << entry.second->size() << ")\n";
	}
}

// new <DataStruct> <name> - Creates a new data structure object called <name>
void newCommand(std::string type, std::string name) {
	if (structures.count(name) > 0) {
		std::cout << name << " already exists.\n";
		return;
	}
	std::unique_ptr<DataStructure> created = createStructure(type);
	if (created == NULL) {
		std::cout << type << " isn't a data structure. Options: LL, stack, queue, heap, tree\n";
		return;
	}
	std::cout << "Created " << created->typeName() << " " << name << "\n";
	structures[name] = std::move(created);
}

// add <name> <value> [head] - Adds a value, head puts it at the front of a linked list
void addCommand(DataStructure* ds, std::string value, std::string position) {
	if (position == "") {
		ds->add(value);
	}
	else if (toLower(position) == "head" && dynamic_cast<LinkedList*>(ds) != NULL) {
		dynamic_cast<LinkedList*>(ds)->insertNodeHead(value);
	}
	else {
		displayHandler(3);
		return;
	}
	ds->view();
}

// remove <name> [value] - Removes a value, stack, queue and heap always remove their next element
void removeCommand(DataStructure* ds, std::vector<std::string> args) {
	if (ds->removeNeedsValue() && args.size() != 3) {
		std::cout << "A " << ds->typeName() << " needs to know which value to remove: remove <name> <value>\n";
		return;
	}
	std::string value = ds->removeNeedsValue() ? args[2] : "";
	if (!ds->remove(value)) {
		std::cout << "Nothing was removed.\n";
		return;
	}
	ds->view();
}

// search <name> <value> - Says if the value is in the data structure
void searchCommand(DataStructure* ds, std::string value) {
	if (ds->search(value)) {
		std::cout << "Found " << value << "\n";
	}
	else {
		std::cout << value << " was not found\n";
	}
}

// edit <name> <old> <new> - Replaces a value
void editCommand(DataStructure* ds, std::string oldValue, std::string newValue) {
	if (!ds->canEdit()) {
		std::cout << "A " << ds->typeName() << " only changes at its ends, so it can't be edited.\n";
		return;
	}
	if (!ds->edit(oldValue, newValue)) {
		std::cout << "Nothing was edited.\n";
		return;
	}
	ds->view();
}

// Runs a command that has already been confirmed to exist. Returns false when the program should close
bool RunCommand(std::string command, std::vector<std::string> args) {

	if (command == "exit") {
		return false;
	}
	if (command == "help" && args.size() == 1) {
		helpCommand();
	}
	else if (command == "dsls" && args.size() == 1) {
		dslsCommand();
	}
	else if (command == "new" && args.size() == 3) {
		newCommand(args[1], args[2]);
	}
	else if (command == "view" && args.size() == 2) {
		DataStructure* ds = findStructure(args[1]);
		if (ds != NULL) ds->view();
	}
	else if (command == "add" && (args.size() == 3 || args.size() == 4)) {
		DataStructure* ds = findStructure(args[1]);
		if (ds != NULL) addCommand(ds, args[2], args.size() == 4 ? args[3] : "");
	}
	else if (command == "remove" && (args.size() == 2 || args.size() == 3)) {
		DataStructure* ds = findStructure(args[1]);
		if (ds != NULL) removeCommand(ds, args);
	}
	else if (command == "search" && args.size() == 3) {
		DataStructure* ds = findStructure(args[1]);
		if (ds != NULL) searchCommand(ds, args[2]);
	}
	else if (command == "edit" && args.size() == 4) {
		DataStructure* ds = findStructure(args[1]);
		if (ds != NULL) editCommand(ds, args[2], args[3]);
	}
	else if (command == "rm" && args.size() == 2) {
		if (findStructure(args[1]) != NULL) {
			structures.erase(args[1]);
			std::cout << "Deleted " << args[1] << "\n";
		}
	}
	else {
		displayHandler(3);
	}
	return true;
}

// Handles user inputted commands. Returns false when the program should close
bool UserInput() {
	std::string commandInput;
	std::string temp;
	std::vector<std::string> cmdV = {};

	std::cout << "DSMNGR>>> ";
	if (!std::getline(std::cin, commandInput)) {
		return false;
	}

	//split inputted commands and adds them to a vector cmdV, quotes around names are optional so they get taken off
	std::istringstream line_stream(commandInput);
	while (line_stream >> temp) {
		temp.erase(std::remove(temp.begin(), temp.end(), '\''), temp.end());
		if (temp != "") {
			cmdV.push_back(temp);
		}
	}

	if (cmdV.empty()) {
		return true;
	}

	//confirm command exists
	std::string command = toLower(cmdV[0]);
	if (std::find(cmds.begin(), cmds.end(), command) == cmds.end()) {
		displayHandler(2);
		return true;
	}

	//run command
	return RunCommand(command, cmdV);
}

int main() {

	//Startup
	displayHandler(1);

	while (UserInput()) {
	}

	return 0;
}
