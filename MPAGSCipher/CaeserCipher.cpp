#include <vector>
#include <iostream>
#include <math.h>
#include "CaeserCipher.hpp"

std::string CaeserCipher( const std::string& inputText, const int key, const bool encrypt)
{
	/* Basic caeser cipher able to 
		- encrypt text by shift key
		- decrypt text by shift key */
	
	// Make alphabet vector
	const std::vector<char> alphabet{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	
	// Add a typedef that assigns another name for the given type for clarity
	typedef std::vector<std::string>::size_type size_type;
	const size_type nAlphabetTemp {alphabet.size()}; // This is done because I couldn't get .size() to work with int
	const int nAlphabet = nAlphabetTemp; // Make size an integer to allow comparisons with ints later.
	
	// Make output string
	std::string outputString {""};
	
	// Initialise temporary shift variable to force key between |0-25|
	int shiftTemp{1};
	
	// If encrypting leave sign of key unchanged, and force key between |0-25|
	if (key < 0 && encrypt) shiftTemp = fmod(key,-25);
	else if (key >=0 && encrypt) shiftTemp = fmod(key,25);
	
	// If decyphering reverse sign of key, and force key between |0-25|
	else if (key < 0) shiftTemp = -fmod(key,-25);
	else shiftTemp = -fmod(key,25);
	
	// Make const shift
	const int shift{shiftTemp};
	
	// Loop over the input text and shift letters
	for ( const char& element : inputText){
		for( int count {0}; count < nAlphabet; count++) {
			if (element == alphabet[count]) {
				if ( ( count >= std::abs(shift) && shift < 0 ) || ( count < nAlphabet - shift && shift >=0) ) { // If shift < distance to end/start then just shift
					outputString += alphabet[count + shift];
				}
				else if ( shift < 0) {	// If shift is greater than distance to begining of alphabet then shift remaining places from end of alphabet
					outputString += alphabet[nAlphabet - (std::abs(shift) - count)];
				}
				else {	// If shift is greater than distance to end of alphabet then shift remaining places from begining of alphabet
					outputString += alphabet[(shift - (nAlphabet - 1 - count)) - 1];	
				}
			}	
		}	
	}
		
	return outputString;
	
}

