#ifndef MPAGSCIPHER_CAESERCIPHER_HPP
#define MPAGSCIPHER_CAESERCIPHER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <math.h>

// Runs Caeser Cipher
std::string CaeserCipher( const std::string& inputText, const int key, const bool encrypt);

#endif // MPAGSCIPHER_CAESERCIPHER_HPP