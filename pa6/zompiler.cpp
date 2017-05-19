// zompiler.cpp : Defines the entry point for the console application.
//

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "node.h"
#include <fstream>

extern int g_LineNumber;
extern NBlock* g_MainBlock;

extern int zompilerparse();
extern FILE* zompilerin;

int main(int argc, char* argv[])
{
	// Read input from the first command line parameter
	zompilerin = fopen(argv[1], "r");
	
	// Start the parse
	zompilerparse();
	
	// TODO: CodeGen from g_MainBlock
    CodeContext myContext;
    if (g_MainBlock != nullptr)
    {
        g_MainBlock->CodeGen(myContext);
    }
    
    // int size = static_cast<int>(myContext.mOps.size());
    // std::cout << "go to size =" << myContext.mGoTos.size() << std::endl;
    
    for (auto it = myContext.mGoTos.rbegin(); it != myContext.mGoTos.rend(); it++)
    {
        if ((std::next(it))->second == (*it).first && (*it).second == 1)
        {
            myContext.mOps[(std::next(it))->first-1] = "goto,1";
            (std::next(it))->second = (*it).second;
        }
    }
    
    std::ofstream outfile;
    outfile.open("out.zom");
    for (auto it = myContext.mOps.begin(); it != myContext.mOps.end(); it++)
    {
        outfile << (*it) << std::endl;
    }
    
	
	// Close the file stream
	fclose(zompilerin);

	return 0;
}

void zompilererror(const char* s)
{
	std::cout << s << " on line " << g_LineNumber << std::endl;
}
