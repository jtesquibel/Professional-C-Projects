//
//  FastaTranslation.hpp
//  dnawx-mac
//
//  Created by Jonathan Esquibel on 3/5/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef FastaTranslation_hpp
#define FastaTranslation_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

class FastaTranslation
{
public:
    FastaTranslation(std::string sequence);
    std::map<char, std::pair<std::string, int>> GetMap();
private:
    // std::map<char, int> mAcids;
    std::map<char, std::pair<std::string, int>> mAcids;
};

#endif /* FastaTranslation_hpp */
