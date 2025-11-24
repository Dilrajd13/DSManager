#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "LinkedList.h"

void RunCommand(std::string name,std::vector<std::string> cmdRun) {
	
	for (int i = 0; i < cmdRun.size(); i++) {
		//temp need to make functional system that can see order of commands
		if (cmdRun[i] == "new") {
			LinkedList LL;
		}
	}

	//TOdo Run the command and make the linkedlist class
}

// Handles user inputted commands
void UserInput() {
	std::string commandInput;
	std::string temp;

	size_t startQ;
	size_t endQ;

	//command list 
	std::vector<std::string> cmds = { "help","DSLS","new","LL","view" };
	
	std::vector<std::string> cmdV = {};
	std::string name;
	std::vector<std::string> cmdOut;
	std::vector<std::string> cmdRun;
	std::cout << "DSMNGR>>> ";
	std::getline(std::cin,commandInput);
	
	//split inputted commands and adds them to a vector cmdV
	std::istringstream line_stream(commandInput);
		while (line_stream >> temp)
			cmdV.push_back(temp);
	
	// Loops over vector cmdV containing user commands and checks for words with two quotes and adds them a variable name, if word has no quotes or only one quote it adds command to vector cmdOut
		for (int i = 0; i < cmdV.size(); i++) {

			startQ = cmdV[i].find('\'');
			if (startQ == std::string::npos) {
				cmdOut.push_back(cmdV[i]);
				continue;
			}
				endQ = cmdV[i].find('\'', startQ + 1);
				if (endQ == std::string::npos) {
					cmdOut.push_back(cmdV[i]);
				continue;
				}
				name = cmdV[i];
				
			}
		
	//confirm command exists- Loops through vector cmdOut and outputs valid when the command matches a real command and does nothing when command is not a real one from vector cmds
		if (!cmdOut.empty()) {
			for (int i = 0; i < cmdOut.size(); i++) {
				for (int j = 0; j < cmds.size(); j++) {
					if (cmdOut[i] == cmds[j]) {
						//std::cout << "VALID";
						cmdRun.push_back(cmdOut[i]);
						break;
					}

				}
			}
		}
		
	//run command
		RunCommand(name, cmdRun);

}

//Prints text for startup, errors, etc..
void displayHandler(int x) {
	
	//Startup Text = 1
	if (x == 1) {
		std::cout << "Data Structure Manager V1 \n\n";
		std::cout << "Welcome to DS Manager, a Terminal to create, visualize and edit Data Structures.\n";
		UserInput();
	}
	

}

//COMMAND Functions
// help - prints list of commands and description
// DSLS - lists all created objects (like ls )
// new <DataStruct> <name> - Creates a new data structure object called <name>
// view <name> - Prints Visual representation of specified Data Structure <name>






int main() {

	//Startup
	displayHandler(1);
	


	return 0;
}
