# - Main CMake buildscript for mpags-cipher

# - Seet CMake requirements then declare project
cmake_minimum_required(VERSION 3.2)
project(MPAGSCipher VERSION 0.1.0)

set(CMAKE_VERBOSE_MAKEFILE ON)

# - Don't allow C++ Compiler Vendor Ectensions
set(CMAKE_CXX_EXTENSIONS OFF)

# - Use our standard set of flags for the GNU/Clang compilers
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -pedantic -Wshadow")
endif()

# - Declare the build of mpags-cipher main program
add_executable(mpags-cipher
	mpags-cipher.cpp
	MPAGSCipher/TransformChar.cpp
	MPAGSCipher/TransformChar.hpp
	MPAGSCipher/ProcessCommandLine.cpp
	MPAGSCipher/ProcessCommandLine.hpp
	MPAGSCipher/CaeserCipher.cpp
	MPAGSCipher/CaeserCipher.hpp
	MPAGSCipher/ProcessTextFromFile.cpp
	MPAGSCipher/ProcessTextFromFile.hpp
	)
target_include_directories(mpags-cipher
	PRIVATE MPAGSCipher
	)
target_compile_features(mpags-cipher
	PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization cxx_binary_literals
	)
