//
//  NeedWunAlgorithm.hpp
//  dnawx-mac
//
//  Created by Jonathan Esquibel on 3/6/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef NeedWunAlgorithm_hpp
#define NeedWunAlgorithm_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "FastaParse.hpp"
#include "Timer.h"

class NeedWunAlgorithm
{
public:
    NeedWunAlgorithm(const std::string& file1, const std::string& file2, std::string path);
    void RunAlgorithm();
    void PrintResults();
private:
    std::vector<std::vector<short>> mGrid1;
    std::vector<std::vector<char>> mGrid2;
    std::string mHeaderA;
    std::string mHeaderB;
    std::string mSequenceA;
    std::string mSequenceB;
    std::string mOutputSequenceA;
    std::string mOutputSequenceB;
    std::string mOutputPath;
    int mMatchScore;
    int mMismatchScore;
    int mGapScore;
    int mFinalScore;
};

#endif /* NeedWunAlgorithm_hpp */
