//
//  PasswordCrack.cpp
//  password-mac
//
//  Created by Jonathan Esquibel on 2/8/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "PasswordCrack.hpp"

PasswordCrack::PasswordCrack(std::string fileName1, std::string fileName2)
{
    this->file1 = fileName1;
    this->file2 = fileName2;
    myUnMap.rehash(100000);
    this->ReadFile();
}

void PasswordCrack::ReadFile()
{
    timer.start();
    std::ifstream dictFile(file1);
    std::string line;
    while (std::getline(dictFile, line))
    {
        unsigned char hash[20];
        char hex_str[41];
        sha1::calc(line.c_str(), line.length(), hash);
        sha1::toHexString(hash, hex_str);
        myUnMap.insert(std::make_pair(hex_str, line));
    }
    
    
    dictFile.close();
    
    this->DictionaryLookup();
}

void PasswordCrack::DictionaryLookup()
{
    std::ifstream passFile(file2);
    std::string line2;
    int entryNum = 0;
    while (std::getline(passFile, line2))
    {
        std::unordered_map<std::string, std::string>::const_iterator it = myUnMap.find(line2);
        if (it == myUnMap.end())
        {
            // then it was not found
            Password *p = new Password(entryNum, line2, "??");
            unsolved.push_back(*p);
            myMap.insert(std::make_pair(entryNum, *p));
        }
        else
        {
            // then it was found
            Password *p = new Password(entryNum, line2, it->second);
            myMap.insert(std::make_pair(entryNum, *p));
        }
        entryNum++;
    }
    
    passFile.close();
    
    this->BruteForce(35, 4);

}

void PasswordCrack::BruteForce(int base, int length)
{
    std::vector<int> attempt = {0,0,0,0};
    int size = 1;
    
    for (int j = 0; j < pow(36, size); j++)
    {
        unsigned char hash[20];
        char hex_str[41];
        sha1::calc(this->NumtoString(attempt).substr(this->NumtoString(attempt).size()-size).c_str(), size, hash);
        // sha1::calc(this->NumtoString(attempt).c_str(), size, hash);
        sha1::toHexString(hash, hex_str);
        for (std::vector<Password>::iterator it = unsolved.begin(); it != unsolved.end(); ++it)
        {
            // std::cout << *it << std::endl;
            if (it->hash == hex_str)
            {
                // then brute force cracked the password
                std::cout << "Brute force worked" << std::endl;
                std::map<int, Password>::iterator itt = myMap.find(it->row);
                if (itt != myMap.end())
                {
                    itt->second.solution = this->NumtoString(attempt).substr(this->NumtoString(attempt).size()-size);
                }

            }
        }
        
        if (attempt[attempt.size()-1] == 35)
        {
            if (size == 1)
            {
                size++;
            }
            attempt[attempt.size()-1] = 0;
            if (attempt[attempt.size()-2] == 35)
            {
                if (size == 2)
                {
                    size++;
                }
                attempt[attempt.size()-2] = 0;
                if (attempt[attempt.size()-3] == 35)
                {
                    if (size == 3)
                    {
                        size++;
                    }
                    attempt[attempt.size()-3] = 0;
                    if (attempt[attempt.size()-4] == 35)
                    {
                        size++;
                        break;
                    }
                    // attempt
                    else
                    {
                        attempt[attempt.size()-4]++;
//                        unsigned char hash[20];
//                        char hex_str[41];
//                        sha1::calc(this->NumtoString(attempt).substr(this->NumtoString(attempt).size()-size).c_str(), size, hash);
//                        // sha1::calc(this->NumtoString(attempt).c_str(), size, hash);
//                        sha1::toHexString(hash, hex_str);
//                        for (std::vector<Password>::iterator it = unsolved.begin(); it != unsolved.end(); ++it)
//                        {
//                            // std::cout << *it << std::endl;
//                            if (it->hash == hex_str)
//                            {
//                                // then brute force cracked the password
//                                std::cout << "Brute force worked" << std::endl;
//                                std::map<int, Password>::iterator itt = myMap.find(it->row);
//                                if (itt != myMap.end())
//                                {
//                                    itt->second.solution = this->NumtoString(attempt).substr(this->NumtoString(attempt).size()-size);
//                                }
//                                
//                            }
//                        }

                    }
                }
                else
                {
                    attempt[attempt.size()-3]++;
                }
            }
            else
            {
                attempt[attempt.size()-2]++;
            }
        }
        else
        {
            attempt[attempt.size()-1]++;
        }
        
        // std::cout << attempt[0] << " " << attempt[1] << " " << attempt[2] << " " << attempt[3] << std::endl;
        
    }
    
    double elapsed = timer.getElapsed();
    std::cout << "Time to load dictionary = " << elapsed << std::endl;

    
    this->PrintToFile();

}

std::string PasswordCrack::NumtoString(std::vector<int> attempt)
{
    char alphabetNum[37] = "abcdefghijklmnopqrstuvwxyz0123456789";
    char pass[5];
    for (int i = 0; i < attempt.size(); i++)
    {
        pass[i] = alphabetNum[attempt[i]];
    }
    
    // std::cout << pass << std::endl;
    return pass;
    
}



//void PasswordCrack::ParallelBrute()
//{
//    tbb::parallel_invoke([this]
//    {
//        
//    });
//}


void PasswordCrack::PrintToFile()
{
    std::ofstream outFile;
    outFile.open("pass_solved.txt");

    for (std::map<int, Password>::iterator it = myMap.begin(); it != myMap.end(); ++it)
    {
        outFile << it->second.hash << "," <<  it->second.solution << std::endl;
    }
    
    outFile.close();

}
