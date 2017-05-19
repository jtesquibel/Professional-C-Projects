//
//  FastaParse.cpp
//  dnawx-mac
//
//  Created by Jonathan Esquibel on 3/5/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "FastaParse.hpp"

FastaParse::FastaParse(std::string path)
{
    std::ifstream::pos_type size;
    // std::cout << "path = " << path << std::endl;

    // Open the file for input, and start ATE (at the end)
    std::ifstream file (path, std::ios::in|std::ios::ate);
    
    if (file.is_open())
    {
        size = file.tellg(); // Save the size of the file
        path.reserve();
        file.seekg (0, std::ios::beg); // Seek back to start of file
        char c;
        std::string header;
        getline(file, header);
        // std::cout << "header = " << header << std::endl;
        try
        {
            TestHeader(header);
        }
        catch (std::exception &e)
        {
            wxMessageBox("FASTA file is invalid", "Error", wxOK | wxICON_ERROR);
            std::exit(EXIT_FAILURE);
        }
        mHeader = header.substr(1);
        while (file.get(c))
        {
            try
            {
                if (c != 'T' && c != 'C' && c != 'G' && c != 'A' && c != '\n' && c != '\r' && c != '\xff')
                {
                    // throw file load exception
                    throw FileLoadExcept();
                }
                if (c == '\n' || c == '\r' || c == '\xff')
                {
                    continue;
                }
                mSequence += c;
            }
            catch (std::exception &e)
            {
                wxMessageBox("FASTA file is invalid", "Error", wxOK | wxICON_ERROR);
                std::exit(EXIT_FAILURE);
            }
        }
        
        file.close();
        
    }


}

void FastaParse::TestHeader(std::string header)
{
    if (header[0] != '>')
    {
        // throw file load exception because header is invalid
        throw FileLoadExcept();
    }
}

//void FastaParse::TestSequence(std::string sequence)
//{
//    
//}

std::string FastaParse::GetHeader()
{
    return mHeader;
}

std::string FastaParse::GetSequence()
{
    return mSequence;
}
