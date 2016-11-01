#include <iostream>
#include <string>
#include <fstream>
#include "ProcessTextFromFile.hpp"

bool processTextFromFile( const std::string& inputFile, std::string& inputString, char& inputChar )
{
	/* Function to read text from a file
		returns a bool of whether read was successful or not*/
	
	std::ifstream in_file {inputFile};
	bool ok_to_read = in_file.good(); 
	if (ok_to_read) {	// If file can be read, assign characters to input string
		std::cout << "Input has been taken from " << inputFile << std::endl;
		while(in_file >> inputChar){
			inputString += inputChar;
		}
	}
	else {	// If can't read file return false
		return false;
	}
 	return true;
}