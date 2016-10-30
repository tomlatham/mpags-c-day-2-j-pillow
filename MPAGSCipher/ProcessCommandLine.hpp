#ifndef MPAGSCIPHER_PROCESSCOMMANDLINE_HPP
#define MPAGSCIPHER_PROCESSCOMMANDLINE_HPP

#include <string>
#include <vector>

// Transliterates char to string
bool processCommandLine( const std::vector<std::string>& cmdLineArgs, bool& helpRequested, bool& encrypt, bool& decrypt, bool& caeserCipher, int& key, bool& versionRequested, std::string& inputFile, std::string& outputFile);

#endif // MPAGSCIPHER_PROCESSCOMMANDLINE_HPP