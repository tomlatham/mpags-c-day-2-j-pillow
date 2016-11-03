// Standard Library includes
#include <iostream>
#include <string>
#include <vector>

#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"
#include "CaeserCipher.hpp"
#include "ProcessTextFromFile.hpp"

// Main function of the mpags-cipher program
int main(int argc, char* argv[])
{
	// Convert the command-line arguments into a more easily usable form
	const std::vector<std::string> cmdLineArgs {argv, argv+argc};

	// Options that might be set by the command-line arguments
	bool helpRequested {false};
	bool versionRequested {false};
	bool encrypt {true};
	bool caeserCipher {false};
	size_t key {0};
	std::string inputFile {""};
	std::string outputFile {""};

	bool commandLineProcessedGood {processCommandLine(cmdLineArgs, helpRequested, encrypt, caeserCipher, key, versionRequested, inputFile, outputFile)};
	
	if (commandLineProcessedGood == false){
		std::cerr << "[error] Problem processing command line arguments" << std::endl;
		return 1;
	}

	// Handle help, if requested
	if (helpRequested) {
		// Line splitting for readability
		std::cout
			<< "Usage: mpags-cipher [-i <file>] [-o <file>] [--caeser] [-e or -d] [-k <number>]\n\n"
			<< "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
			<< "Available options:\n\n"
			<< "  -h|--help        Print this help message and exit\n\n"
			<< "  --version        Print version information\n\n"
			<< "  -i FILE          Read text to be processed from FILE\n"
			<< "                   Stdin will be used if not supplied\n\n"
			<< "  -o FILE          Write processed text to FILE\n"
			<< "                   Stdout will be used if not supplied\n\n"
			<< "  --caeser         Use to encrypt/decrypt via caeser cipher\n\n"
			<< "  -k|--key VALUE   Specify key VALUE for use in cipher\n"
			<< "                   VALUE can be positive or negative, but must be integer\n\n"
			<< "  -e|--encrypt     Use to encrypt input\n"
			<< "                   Cannot be used with -d|--decrypt\n\n"
			<< "  -d|--decrypt     Use to decrypt input\n"
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
		std::cout << "0.2.0" << std::endl;
		return 0;
  	}

  	// Initialise variables for processing input text
  	char inputChar {'x'};
	std::string inputString {""};
  	std::string translitString {""};
	std::string outputString {""};

	if (caeserCipher) {
		std::cout << "You have selected to use the Caeser cipher." << std::endl;
	} else {
		std::cout << "You have not seleted to use a cipher. Text will only be transliterated." << std::endl;
	}
		
	if (!inputFile.empty()) {	// Read input from given file
		bool fileReadGood = processTextFromFile( inputFile, inputString ); // Read text from file
		if (fileReadGood == false) { // If file can't be read give error and return 1
			std::cerr << "[error] Problem reading from file" << std::endl;
			return 1;
		}
	}
	else { // If no input file given then use user input
		std::cout << "Input file not specified. Please input desired text into terminal:" << std::endl;
		while(std::cin >> inputChar){
			inputString += inputChar;
		}
	}
		
	// Transliterate the input string
	translitString = transformChar(inputString); 

	if (caeserCipher) {

		//Run Caeser Cipher
		outputString = CaeserCipher(translitString,key,encrypt);	

	} // End Caeser implementation
	
	else {
		
		// Set outputString. This is done to remain consistent with using the cipher.
		outputString = translitString;
		
	} // End transliteration only implementation
	
	
  	// Output the transliterated/ciphered text
	if (!outputFile.empty()) { // If file is given, write to file
 		std::ofstream out_file {outputFile};
		bool ok_to_write = out_file.good();
		if (ok_to_write) {
			std::cout << "Output has been written to " << outputFile << std::endl;
			out_file << outputString << std::endl;
		}
		else {
			std::cerr << "[error] Output file is not good to write to" << std::endl;
			std::cout << outputString << std::endl;
		}
	}
	else { // If no file is specified output to terminal
		std::cout 
			<< "Output file not specified. Printing to terminal:\n"
			<< outputString << std::endl;
		return 0;
	}
	
	
	// No requirement to return from main, but we do so for clarity
  	// and for consistency with other functions
	return 0;
}
