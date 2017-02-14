// Main.cpp : Defines the entry point for the console application.
//

#include "RleTests.h"
#include "RleData.h"
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include "RleFile.h"

void Part1Tests()
{
	TestFixtureFactory::theInstance().runTests();
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		// Just the tests
		Part1Tests();
	}
	else
	{
		// TODO: Get the file name from argv[1] and either compress/decompress
        std::string fileName = argv[1];
        std::cout << "Filename = " << fileName << std::endl;
        int fileNameSize = static_cast<unsigned int>(fileName.size());
        std::cout << "Filename size = " << fileNameSize << std::endl;
        std::string endName = fileName.substr(fileNameSize-4,4);
        // if it ends it ".rl1" then decomporess
        if (endName.compare(".rl1") == 0)
        {
            RleFile filee;
            filee.ExtractArchive(fileName);
        }
        // if not then compress
        else
        {
            RleFile filee;
            filee.CreateArchive(fileName);
        }
	}
	return 0;
}

