// Standard Library includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"
#include "CaeserCipher.hpp"

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
	bool encrypt {false};
	bool decrypt {false};
	bool caeserCipher {false};
	int key {0};
	std::string inputFile {""};
	std::string outputFile {""};

	bool commandLineProcessedGood {processCommandLine(cmdLineArgs, helpRequested, encrypt, decrypt, caeserCipher, key, versionRequested, inputFile, outputFile)};
	
	if (commandLineProcessedGood == false){
		std::cout << "Command line error" << std::endl;
		return 1;
	}

	// Handle help, if requested
	if (helpRequested) {
		// Line splitting for readability
	    std::cout
			<< "Usage: mpags-cipher [-i <file>] [-o <file>] [--caeser] [-e] [-k <number>]\n\n"
			<< "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      		<< "Available options:\n\n"
      		<< "  -h|--help        Print this help message and exit\n\n"
      		<< "  --version        Print version information\n\n"
      		<< "  -i FILE          Read text to be processed from FILE\n"
      		<< "                   Stdin will be used if not supplied\n\n"
      		<< "  -o FILE          Write processed text to FILE\n"
      		<< "                   Stdout will be used if not supplied\n\n"
			<< "  --caeser         Use to encrypt/decrypt via caeser cipher\n\n"
			<< "  -k|--key NUMBER  Specify key=NUMBER for use in cipher\n\n"
			<< "  -e|--encrypt     Use to encrypt input\n"
			<< "                   Cannot be used with -d|--decrypt\n\n"
			<< "  -d|decrypt       Use to decrypt input\n"
			<< "                   When decrypting use same key as used for encrypting\n"
			<< "                   E.g. if key to encrypt is 5, key to decrypt is 5, not -5\n"
			<< "                   Cannot be used with -e|--encrypt\n\n";
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
  	std::string translitString{""};
	std::string outputString{""};

	if (caeserCipher) {
		std::cout << "You have selected to use the Caeser cipher." << std::endl;
 	 	// Read in user input from stdin/file
	  	// Or loop over each character from user input
		if (!inputFile.empty()) {
    		std::ifstream in_file {inputFile};
			bool ok_to_read = in_file.good();
			if (ok_to_read) {
				std::cout << "Input has been taken from " << inputFile << std::endl;
				while(in_file >> inputChar){
					translitString += transformChar(inputChar);
				}
			}
			else {
				std::cerr << "[error] Input file is not good to read from" << std::endl;
				return 1; // Return 1 to to indicate program failed
			}
  		}
	
		else { // If no input file given then use user input
			std::cout << "No input file specified, please input desired text into terminal:" << std::endl;
	  		while(std::cin >> inputChar){
				translitString += transformChar(inputChar);
  			}
		}
		
		const bool encryptDecrypt = (encrypt == true) ? true : false; // See if encrypting or decrypting has been selected
		
		outputString = CaeserCipher(translitString,key,encryptDecrypt);
		//std::cout << "The output from caeser is: " << outputString << std::endl;		
	}
	
	else {
		std::cout << "You have not seleted to use a cipher. Text will only be transliterated." << std::endl;
 	 	// Read in user input from stdin/file
	  	// Or loop over each character from user input
		if (!inputFile.empty()) {
    		std::ifstream in_file {inputFile};
			bool ok_to_read = in_file.good();
			if (ok_to_read) {
				std::cout << "Input has been taken from " << inputFile << std::endl;
				while(in_file >> inputChar){
					translitString += transformChar(inputChar);
				}
			}
			else {
				std::cerr << "[error] Input file is not good to read from" << std::endl;
				return 1; // Return 1 to indicate program failed
			}
  		}
	
		else { // If no input file given then use user input
			std::cout << "No input file specified, please input desired text into terminal:" << std::endl;
	  		while(std::cin >> inputChar){
				translitString += transformChar(inputChar);
  			}
		}
		outputString = translitString;
	}
	
	
  	// Output the transliterated/ciphered text
	if (!outputFile.empty()) {
 		std::ofstream out_file {outputFile};
		bool ok_to_write = out_file.good();
		if (ok_to_write) {
			std::cout << "Output has been written to " << outputFile << std::endl;
			out_file << outputString << std::endl;
		}
		else {
			std::cerr << "[error] Output file is not good to write to" << std::endl;
			std::cout << "Output text is: " << outputString << std::endl;
		}
	}
	else {
		std::cout << "The output string is: " << outputString << std::endl;
		return 0;
	}
  	// No requirement to return from main, but we do so for clarity
  	// and for consistency with other functions
	
  	return 0;
}