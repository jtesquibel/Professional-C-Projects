// Main.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <utility>
#include <iterator>
#include <vector>
#include <tbb/parallel_invoke.h>
#include "Sha1.h"
#include "Timer.h"
#include "BruteForce.h"
#include "Password.hpp"
#include "PasswordCrack.hpp"



int main(int argc, char* argv[])
{
    
    if (argc == 2)
    {
        // return the SHA-1 hash of the argument
        unsigned char hash[20];
        std::string argument = argv[1];
        sha1::calc(argv[1], argument.length(), hash);
        char hex_str[41];
        sha1::toHexString(hash, hex_str);
    }
    else if (argc == 3)
    {
        PasswordCrack p(argv[1], argv[2]);
    }
    
    
    
    
	return 0;
}


