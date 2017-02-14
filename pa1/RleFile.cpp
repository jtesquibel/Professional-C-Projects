#include "RLEFile.h"
#include "RleData.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "FileSystem.h"

void RleFile::CreateArchive(const std::string& source)
{
	// TODO
    std::ifstream::pos_type size;
    char* memblock;
    // Open the file for input, in binary mode, and start ATE (at the end)
    std::ifstream file (source, std::ios::in|std::ios::binary|std::ios::ate);
    if (file.is_open())
    {
        size = file.tellg(); // Save the size of the file
        std::cout << "Original size = " << size << std::endl;
        memblock = new char [static_cast<unsigned int>(size)];
        file.seekg (0, std::ios::beg); // Seek back to start of file
        file.read (memblock, size);
        file.close();
        
        // File data has now been loaded into memblock array
        this->mData.Compress(memblock, static_cast<unsigned int>(size));
        
        
        // Make sure to clean up!
        delete[] memblock;
    }
    
    
    std::cout << "mdata size = " << mData.mSize << std::endl;
    
    double percent = 1.00-(static_cast<double>(this->mData.mSize)/static_cast<double>(size));
    int percent2 = percent*100;
    std::cout << "The compression was " << percent2 << " percent effective!" << std::endl;
    std::string filename = source+".rl1";
    
    this->mHeader.sig[0] = 'r';
    this->mHeader.sig[1] = 'l';
    this->mHeader.sig[2] = 'e';
    this->mHeader.sig[3] = '\x01';
    this->mHeader.fileSize = static_cast<unsigned int>(size);
    this->mHeader.fileNameLength = static_cast<unsigned char>(source.length());
    this->mHeader.fileName = source;
    
    // Open the file for output, in binary mode, and overwrite an existing file
    std::ofstream arc(filename, std::ios::out|std::ios::binary|std::ios::trunc);
    if (arc.is_open())
    {
        // Use arc.write function to write data here
        arc.write(mHeader.sig, 4);
        arc.write(reinterpret_cast<char*>(&(mHeader.fileSize)), 4);
        arc.write(reinterpret_cast<char*>(&(mHeader.fileNameLength)), 1);
        arc.write(mHeader.fileName.c_str(), source.length());
        arc.write(mData.mData, mData.mSize);
    }
}

void RleFile::ExtractArchive(const std::string& source)
{
	// TODO
    std::ifstream::pos_type size;
    char* memblock;
    std::ifstream file (source, std::ios::in|std::ios::binary|std::ios::ate);
    if (file.is_open())
    {
        std::cout << "in decom" << std::endl;
        size = file.tellg(); // Save the size of the file
        memblock = new char [static_cast<unsigned int>(size)];
        file.seekg (0, std::ios::beg); // Seek back to start of file
        file.read (memblock, size);
        file.close();
        
        if (memblock[0] != 'R' || memblock[1] != 'L' || memblock[2] != 'E' || memblock[3] != '\x01')
        {
            std::cout << "Error with the filename signature, not a valid archive" << std::endl;
            return;
        }
        
        this->mHeader.sig[0] = memblock[0];
        this->mHeader.sig[1] = memblock[1];
        this->mHeader.sig[2] = memblock[2];
        this->mHeader.sig[3] = memblock[3];
        this->mHeader.fileSize = *(reinterpret_cast<int*>(&memblock[4]));
        this->mHeader.fileNameLength = memblock[8];
        int fileNameLen = static_cast<int>(this->mHeader.fileNameLength);
        std::cout << "len = " << fileNameLen << std::endl;
        std::string temp = "";
        for (int i = 0; i < fileNameLen; i++)
        {
            temp = temp+memblock[9+i];
        }
        this->mHeader.fileName = temp;

        this->mData.Decompress(memblock+9+this->mHeader.fileNameLength, static_cast<unsigned int>(size)-9, this->mHeader.fileSize);
        
        // Open the file for output, in binary mode, and overwrite an existing file
        std::ofstream arc(this->mHeader.fileName, std::ios::out|std::ios::binary|std::ios::trunc);
        if (arc.is_open())
        {
            // Use arc.write function to write data here
            arc.write(this->mData.mData,this->mData.mSize);
        }
        
        
        
        
        // Make sure to clean up!
        delete[] memblock;
    }

    
    
    
    
    
    
}
