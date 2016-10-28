// Standard Library includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"

// For std::isalpha and std::isupper
#include <cctype>

//std::string transformChar( const char inputChar );

// Main function of the mpags-cipher program
int main(int argc, char* argv[])
{
	// Convert the command-line arguments into a more easily usable form
	const std::vector<std::string> cmdLineArgs {argv, argv+argc};

	// Options that might be set by the command-line arguments
	bool helpRequested {false};
	bool versionRequested {false};
	std::string inputFile {""};
	std::string outputFile {""};

	bool commandLineProcessedGood {processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile)};
	
	if (commandLineProcessedGood == false){
		std::cout << "Command line error" << std::endl;
		return 1;
	}

	// Handle help, if requested
	if (helpRequested) {
		// Line splitting for readability
    	std::cout
			<< "Usage: mpags-cipher [-i <file>] [-o <file>]\n\n"
			<< "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      		<< "Available options:\n\n"
      		<< "  -h|--help        Print this help message and exit\n\n"
      		<< "  --version        Print version information\n\n"
      		<< "  -i FILE          Read text to be processed from FILE\n"
      		<< "                   Stdin will be used if not supplied\n\n"
      		<< "  -o FILE          Write processed text to FILE\n"
      		<< "                   Stdout will be used if not supplied\n\n";
    		// Help requires no further action, so return from main
    		// with 0 used to indicate success
    	return 0;
	}

  	// Handle version, if requested
  	// Like help, requires no further action,
  	// so return from main with zero to indicate success
  	if (versionRequested) {
    	std::cout << "0.1.0" << std::endl;
    	return 0;
  	}

  	// Initialise variables for processing input text
  	char inputChar {'x'};
  	std::string output_str{""};

  	// Read in user input from stdin/file
  	// Warn that input file option not yet implemented
  	// Loop over each character from user input
  	// (until Return then CTRL-D (EOF) pressed)
	if (!inputFile.empty()) {
    	std::ifstream in_file {inputFile};
		bool ok_to_read = in_file.good();
		if (ok_to_read) {
			while(in_file >> inputChar){
				output_str += transformChar(inputChar);
			}
		}
		else {
			std::cout << "Error: Output file is not good to read to" << std::endl;
			std::cout << "Output text is: " << output_str << std::endl;
		}
  	}
	
	else {
  		while(std::cin >> inputChar){
			output_str += transformChar(inputChar);
  		}
	}
  	// Output the transliterated text
  	// Warn that output file option not yet implemented
  	if (!outputFile.empty()) {
    	std::ofstream out_file {outputFile};
		bool ok_to_write = out_file.good();
		if (ok_to_write) {
			out_file << output_str << std::endl;
		}
		else {
			std::cout << "Error: Output file is not good to write to" << std::endl;
			std::cout << "Output text is: " << output_str << std::endl;
		}
  	}
	else {
		std::cout << output_str << std::endl;
		return 0;
	}
  	// No requirement to return from main, but we do so for clarity
  	// and for consistency with other functions
  	return 0;
}