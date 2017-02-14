//
//  PasswordCrack.hpp
//  password-mac
//
//  Created by Jonathan Esquibel on 2/8/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef PasswordCrack_hpp
#define PasswordCrack_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <utility>
#include <iterator>
#include <cmath>
#include <vector>
#include <tbb/parallel_invoke.h>
#include <string>
#include "Sha1.h"
#include "Timer.h"
#include "Password.hpp"

class PasswordCrack
{
public:
    
    PasswordCrack(std::string fileName1, std::string fileName2);
    
private:
    
    void ReadFile();
    void DictionaryLookup();
    void BruteForce(int base, int length);
    std::string NumtoString(std::vector<int> attempt);
    void ParallelBrute();
    void PrintToFile();
    
    std::string file1;
    std::string file2;
    std::unordered_map<std::string, std::string> myUnMap;
    std::map<int, Password> myMap;
    std::vector<Password> unsolved;
    Timer timer;
    
};

#endif /* PasswordCrack_hpp */
