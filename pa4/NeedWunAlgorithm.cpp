//
//  NeedWunAlgorithm.cpp
//  dnawx-mac
//
//  Created by Jonathan Esquibel on 3/6/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "NeedWunAlgorithm.hpp"
#include <wx/msgdlg.h>

enum MyEnum : char
{
    // Values...
    ID_ABOVE_LEFT='d',
    ID_LEFT='l',
    ID_ABOVE='a'
};

// int matchScore = 1;

NeedWunAlgorithm::NeedWunAlgorithm(const std::string& file1, const std::string& file2, std::string path)
{
    Timer timer;
    timer.Start();
    FastaParse fp(file1);
    mSequenceA = fp.GetSequence();
    mHeaderA = fp.GetHeader();
    FastaParse fpp(file2);
    mSequenceB = fpp.GetSequence();
    mHeaderB = fpp.GetHeader();
    mMatchScore = 1;
    mMismatchScore = -1;
    mGapScore = -1;
    mOutputPath = path;
    RunAlgorithm();
    // std::cout << "elapsed time = " << timer.GetElapsed() << std::endl;
    
    wxString message;
    message.Printf( wxT("Time it took: %f seconds"), timer.GetElapsed());

    wxMessageBox(message);
}

void NeedWunAlgorithm::RunAlgorithm()
{
    // not vector of vectors is row by column
    int columns = static_cast<int>(mSequenceA.length())+1;
    int rows = static_cast<int>(mSequenceB.length())+1;
    mSequenceA = "0" + mSequenceA;
    mSequenceB = "0" + mSequenceB;
   
    // resize the grid
    mGrid1.resize(rows);
    mGrid2.resize(rows);
    for (int i = 0; i < rows; i++)
    {
        mGrid1[i].resize(columns);
        mGrid2[i].resize(columns);
    }
    
    for (int i = 0; i < columns; i++)
    {
        if (i == 0)
        {
            mGrid1[0][0] = 0;
            continue;
        }
        mGrid1[0][i] = i*-1;
        mGrid2[0][i] = ID_LEFT;
    }
    for (int i = 0; i < rows; i++)
    {
        if (i == 0)
        {
            continue;
        }
        mGrid1[i][0] = i*-1;
        mGrid2[i][0] = ID_ABOVE;
    }
    
    for (int i = 1; i < rows; i++)
    {
        for (int j = 1; j < columns; j++)
        {
            int score1;
            if (mSequenceA[j] == mSequenceB[i])
            {
                score1 = mGrid1[i-1][j-1]+mMatchScore;
            }
            else
            {
                score1 = mGrid1[i-1][j-1]+mMismatchScore;
            }
            int score2 = mGrid1[i][j-1]+mGapScore;
            int score3 = mGrid1[i-1][j]+mGapScore;
            if (score1 > score2 && score1 > score3)
            {
                // score 1 wins
                mGrid1[i][j] = score1;
                mGrid2[i][j] = ID_ABOVE_LEFT;
            }
            else if (score2 > score1 && score2 > score3)
            {
                // score 2 wins
                mGrid1[i][j] = score2;
                mGrid2[i][j] = ID_LEFT;
            }
            else if (score3 > score1 && score3 > score2)
            {
                // score 3 wins
                mGrid1[i][j] = score3;
                mGrid2[i][j] = ID_ABOVE;
            }
            else if (score1 > score2 && score2 == score3)
            {
                // score 1 wins
                mGrid1[i][j] = score1;
                mGrid2[i][j] = ID_ABOVE_LEFT;
            }
            else if (score1 > score2 && score1 == score3)
            {
                // score 1 wins
                mGrid1[i][j] = score1;
                mGrid2[i][j] = ID_ABOVE_LEFT;
            }
            else if (score2 > score1 && score2 == score3)
            {
                // score 2 wins
                mGrid1[i][j] = score2;
                mGrid2[i][j] = ID_LEFT;
            }
            else if (score1 == score2 && score2 == score3)
            {
                // score 1 wins
                mGrid1[i][j] = score1;
                mGrid2[i][j] = ID_ABOVE_LEFT;
            }
            else if (score1 == score2 && score2 > score3)
            {
                // score 1 wins
                mGrid1[i][j] = score1;
                mGrid2[i][j] = ID_ABOVE_LEFT;
            }
        }
    }
    
    mFinalScore = mGrid1[rows-1][columns-1];
    
    // now you have the grid properly built
    
    rows--;
    columns--;
    std::cout << "rows,cols = " << rows << ", " << columns <<std::endl;
    std::vector<char> outputSequence1, outputSequence2;
    int count = 0;
    int end = rows+columns;
    while (end != 0)
    {
        if (mGrid2[rows][columns] == 'd')
        {
            // this means above left
            
            outputSequence1.push_back(mSequenceA[columns]);
            outputSequence2.push_back(mSequenceB[rows]);
   
            rows--;
            columns--;
            end -= 2;
        }
        else if (mGrid2[rows][columns] == 'l')
        {
            // this means left
            
            outputSequence1.push_back(mSequenceA[columns]);
            outputSequence2.push_back('_');
            columns--;
            end--;
            
        }
        else if (mGrid2[rows][columns] == 'a')
        {
            // this means above
 
            outputSequence1.push_back('_');
            outputSequence2.push_back(mSequenceB[rows]);
            rows--;
            end--;
        }
        count++;
    }
    
    std::reverse(outputSequence1.begin(), outputSequence1.end());
    std::reverse(outputSequence2.begin(), outputSequence2.end());
    
    std::string output1(outputSequence1.begin(), outputSequence1.end());
    std::string output2(outputSequence2.begin(), outputSequence2.end());
    
    mOutputSequenceA = output1;
    mOutputSequenceB = output2;
    
    
    PrintResults();
    

    
}

void NeedWunAlgorithm::PrintResults()
{
    std::ofstream out(mOutputPath, std::ios::out|std::ios::trunc);

    
    out << "A: " << mHeaderA << std::endl;
    out << "B: " << mHeaderB << std::endl;
    out << "Score: " << mFinalScore << std::endl << std::endl;
    bool a, line, b;
    a = true;
    line = false;
    b = false;
    
    int count = 1;
    int end = 0;
    
    if (mOutputSequenceA.length() <= 70)
    {
        for (int i = 0; i < mOutputSequenceA.length(); i++)
        {
            out << mOutputSequenceA[i];
        }
        out << std::endl;
        for (int i = 0; i < mOutputSequenceA.length(); i++)
        {
            if (mOutputSequenceA[i] == mOutputSequenceB[i])
            {
                out << '|';
            }
            else{
                out << ' ';
            }
        }
        out << std::endl;
        for (int i = 0; i < mOutputSequenceA.length(); i++)
        {
            out << mOutputSequenceB[i];
        }
    }
    else
    {
        for (int i = 0, j = 1; i < mOutputSequenceA.length(); i++, j++)
        {
            if (a == true)
            {
                out << mOutputSequenceA[i];
            }
            if (line == true)
            {
                if (mOutputSequenceA[i] == mOutputSequenceB[i])
                {
                    out << '|';
                }
                else
                {
                    out << ' ';
                }
            }
            if (b == true)
            {
                out << mOutputSequenceB[i];
            }
            
            if (j == 70)
            {
                count++;
                j = 0;
                out << std::endl;
                if (a == true)
                {
                    i -= 70;
                    a = false;
                    line = true;
                }
                else if (line == true)
                {
                    i -= 70;
                    line = false;
                    b = true;
                }
                else if (b == true)
                {
                    out << std::endl;
                    b = false;
                    a = true;
                    end += 70;
                }
            }
        }
    }
    
    out << std::endl;
    for (int i = 0; i < mOutputSequenceA.length()-end; i++)
    {
        if (mOutputSequenceA[i+end] == mOutputSequenceB[i+end])
        {
            out << '|';
        }
        else
        {
            out << ' ';
        }

    }
    out << std::endl;
    for (int i = 0; i < mOutputSequenceA.length()-end; i++)
    {
        out << mOutputSequenceB[i+end];
    }
    
    
    
}
