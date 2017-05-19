//
//  FastaTranslation.cpp
//  dnawx-mac
//
//  Created by Jonathan Esquibel on 3/5/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "FastaTranslation.hpp"

FastaTranslation::FastaTranslation(std::string sequence)
{
    // bool start = false;
    
    mAcids.insert(std::make_pair('M', std::make_pair("Methionine", 0)));
    mAcids.insert(std::make_pair('F', std::make_pair("Phenylalanine", 0)));
    mAcids.insert(std::make_pair('L', std::make_pair("Leucine", 0)));
    mAcids.insert(std::make_pair('S', std::make_pair("Serine", 0)));
    mAcids.insert(std::make_pair('Y', std::make_pair("Tyrosine", 0)));
    mAcids.insert(std::make_pair('C', std::make_pair("Cysteine", 0)));
    mAcids.insert(std::make_pair('W', std::make_pair("Tryptophan", 0)));
    mAcids.insert(std::make_pair('P', std::make_pair("Proline", 0)));
    mAcids.insert(std::make_pair('H', std::make_pair("Histidine", 0)));
    mAcids.insert(std::make_pair('Q', std::make_pair("Glutamine", 0)));
    mAcids.insert(std::make_pair('R', std::make_pair("Arginine", 0)));
    mAcids.insert(std::make_pair('I', std::make_pair("Isoleucine", 0)));
    mAcids.insert(std::make_pair('T', std::make_pair("Threonine", 0)));
    mAcids.insert(std::make_pair('N', std::make_pair("Asparagine", 0)));
    mAcids.insert(std::make_pair('K', std::make_pair("Lysine", 0)));
    mAcids.insert(std::make_pair('V', std::make_pair("Valine", 0)));
    mAcids.insert(std::make_pair('A', std::make_pair("Alanine", 0)));
    mAcids.insert(std::make_pair('D', std::make_pair("Aspartic Acid", 0)));
    mAcids.insert(std::make_pair('E', std::make_pair("Glutamic Acid", 0)));
    mAcids.insert(std::make_pair('G', std::make_pair("Glycine", 0)));
    
    
    char machine [24][4] =
    {
        {0, 0, 1, 0},
        {2, 0, 1, 0},
        {0, 0, 1, 'M'},
        {4,	9, 14, 19},
        {5, 6, 7, 8},
        {'F', 'F', 'L', 'L'},
        {'S', 'S', 'S', 'S'},
        {'Y', 'Y', 0, 0},
        {'C', 'C', 0, 'W'},
        {10, 11, 12, 13},
        {'L', 'L', 'L', 'L'},
        {'P', 'P', 'P', 'P'},
        {'H', 'H', 'Q', 'Q'},
        {'R', 'R', 'R', 'R'},
        {15, 16, 17, 18},
        {'I', 'I', 'I', 'M'},
        {'T', 'T', 'T', 'T'},
        {'N', 'N', 'K', 'K'},
        {'S', 'S', 'R', 'R'},
        {20, 21, 22, 23},
        {'V', 'V', 'V', 'V'},
        {'A', 'A', 'A', 'A'},
        {'D', 'D', 'E', 'E'},
        {'G', 'G', 'G', 'G'}
    };
    int stage = 0;
    for (auto c : sequence)
    {
        if (c == 'T')
        {
            stage = machine[stage][0];
            auto it = mAcids.find(static_cast<char>(stage));
            if (it != mAcids.end())
            {
                mAcids.find(static_cast<char>(stage))->second.second++;
                stage = 3;
            }
        }
        else if (c == 'C')
        {
            stage = machine[stage][1];
            auto it = mAcids.find(static_cast<char>(stage));
            if (it != mAcids.end())
            {
                mAcids.find(static_cast<char>(stage))->second.second++;
                stage = 3;
            }
        }
        else if (c == 'A')
        {
            stage = machine[stage][2];
            auto it = mAcids.find(static_cast<char>(stage));
            if (it != mAcids.end())
            {
                mAcids.find(static_cast<char>(stage))->second.second++;
                stage = 3;
            }
        }
        else if (c == 'G')
        {
            if (stage == 2)
            {
                stage = machine[stage][3];
                mAcids.find(static_cast<char>(stage))->second.second++;
                stage = 3;
                continue;
            }
            stage = machine[stage][3];
            auto it = mAcids.find(static_cast<char>(stage));
            if (it != mAcids.end())
            {
                mAcids.find(static_cast<char>(stage))->second.second++;
                stage = 3;
            }
        }
    }
    
    for (auto it = mAcids.begin(); it != mAcids.end(); it++)
    {
        std::cout << it->first << " = " << it->second.second << std::endl;
    }
    
    mAcids = mAcids;
}

std::map<char, std::pair<std::string, int>> FastaTranslation::GetMap()
{
    return mAcids;
}
