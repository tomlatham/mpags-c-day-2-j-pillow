#include <string>
#include "TransformChar.hpp"

std::string transformChar( const std::string inputString ){	
	/* Transliterates string input
		- Will make characters upper case
		- Change digits to words
		-remove anything non-alphanumeric */
	
	std::string translitString{""};
	
	for ( const char& inputChar : inputString ){
		// Uppercase alphabetic characters
    	if (std::isalpha(inputChar)) {
	      translitString += std::toupper(inputChar);
    	}

    	// Transliterate digits to English words
    	switch (inputChar) {
	    	case '0':
				translitString += "ZERO";
				break;
    	  	case '1':
				translitString += "ONE";
				break;
	      	case '2':
				translitString += "TWO";
				break;
	    	case '3':
				translitString += "THREE";
				break;
    	  	case '4':
				translitString += "FOUR";
				break;
	      	case '5':
				translitString += "FIVE";
				break;
	      	case '6':
				translitString += "SIX";
				break;
      		case '7':
				translitString += "SEVEN";
				break;
      		case '8':
				translitString += "EIGHT";
				break;
      		case '9':
				translitString += "NINE";
				break;
    	}
	}

    // If the character isn't alphabetic or numeric, DONT add it.
    // Our ciphers can only operate on alphabetic characters.
	return translitString;
}