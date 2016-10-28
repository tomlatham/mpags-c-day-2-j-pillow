#include <iostream>
#include <vector>
#include "ProcessCommandLine.hpp"


bool processCommandLine( const std::vector<std::string>& cmdLineArgs, bool& helpRequested, bool& versionRequested, std::string& inputFile, std::string& outputFile){
	// Process command line arguments - ignore zeroth element, as we know this to
 	// be the program name and don't need to worry about it
	
	// Add a typedef that assigns another name for the given type for clarity
	typedef std::vector<std::string>::size_type size_type;
	const size_type nCmdLineArgs {cmdLineArgs.size()};
	
	for (size_type i {1}; i < nCmdLineArgs; ++i) {

		if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
			helpRequested = true;
		}
    
		else if (cmdLineArgs[i] == "--version") {
    		versionRequested = true;
   		}
    
		else if (cmdLineArgs[i] == "-i") {
    	// Handle input file option
    	// Next element is filename unless -i is the last argument
    		if (i == nCmdLineArgs-1) {
				std::cerr << "[error] -i requires a filename argument" << std::endl;
				// exit main with non-zero return to indicate failure
				return false;
      		}
      		else {
				// Got filename, so assign value and advance past it
				inputFile = cmdLineArgs[i+1];
				++i;
      		}
 		}
    
		else if (cmdLineArgs[i] == "-o") {
    		// Handle output file option
    		// Next element is filename unless -o is the last argument
    		if (i == nCmdLineArgs-1) {
				std::cerr << "[error] -o requires a filename argument" << std::endl;
				// exit main with non-zero return to indicate failure
				return false;
    		}
    		else {
				// Got filename, so assign value and advance past it
				outputFile = cmdLineArgs[i+1];
				++i;
    		}
    	}
    
		else {
    		// Have an unknown flag to output error message and return non-zero
    		// exit status to indicate failure
    		std::cerr << "[error] unknown argument '" << cmdLineArgs[i] << "'\n";
    		return false;
    	}
	}
	return 0;
}