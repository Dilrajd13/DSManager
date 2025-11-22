#include <iostream>
#include <string>
#include <sstream>

// Handles user inputted commands
void UserInput() {
	std::string commandInput;
	// not best but used for testing- should fix this later
	std::string command1;
	std::string command2;

	std::cout << "DSMNGR>>> ";
	std::getline(std::cin,commandInput);

	//split inputted commands *For now only takes the first two words and ignores rest*
	std::istringstream line_stream(commandInput);
	line_stream >> command1 >> command2;
	std::cout << command1 << command2;


}
//Prints text for startup, errors, etc..
void displayHandler(int x) {
	
	//Startup Text = 1
	if (x == 1) {
		std::cout << "Data Structure Manager V1 \n\n";
		std::cout << "Welcome to DS Manager, a Terminal to create, visualize and edit Data Structures.\n";
		UserInput();
	}
	else {
		std::cout << "ERROR";
	}

}







int main() {

	//Startup
	displayHandler(1);



	return 0;
}
