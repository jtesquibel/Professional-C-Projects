//
//  FastaParse.hpp
//  dnawx-mac
//
//  Created by Jonathan Esquibel on 3/5/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef FastaParse_hpp
#define FastaParse_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include <wx/toolbar.h>
#include <wx/image.h>
#include <wx/colordlg.h>
#include <wx/textdlg.h>
#include <wx/filedlg.h>
#include "Exceptions.h"

class FastaParse
{
public:
    FastaParse(std::string path);
    void TestHeader(std::string header);
    void TestSequence(std::ifstream file);
    std::string GetHeader();
    std::string GetSequence();
private:
    std::string mHeader;
    std::string mSequence;
};

#endif /* FastaParse_hpp */
