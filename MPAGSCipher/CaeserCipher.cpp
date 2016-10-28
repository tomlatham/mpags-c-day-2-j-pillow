#include <vector>
#include <iostream>

std::string CaeserCipher( const std::string& inputText, const size_t key, const bool encrypt)
{
	/* Basic caeser cipher able to 
		- encrypt text by shift key
		- decrypt text by shift key */
	
	// Make alphabet vector
	const std::vector<char> alphabet{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	// Add a typedef that assigns another name for the given type for clarity
	typedef std::vector<std::string>::size_type size_type;
	const size_type nAlphabet {alphabet.size()};
	
	// Make output string
	std::string outputString {""};
	
	// Make sure key is between 0-25;
	
	
	// Loop over the input text
	for ( char& element : inputText){
		for( size_type count {0}; count < nAlphabet; count++) {
			if (element == alphabet[count]) {
				;
			}	
		}	
	}
	
	return outputString;
	
}