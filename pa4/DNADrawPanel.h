//
//  DNADrawPanel.h
//  DNAwx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#pragma once
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <map>

class DNADrawPanel : public wxPanel
{
public:
    DNADrawPanel(wxFrame* parent);
	void PaintNow();
    void SetHeader(std::string header);
    void SetAcids(std::map<char, std::pair<std::string, int>>);
protected:
    void PaintEvent(wxPaintEvent & evt);
	void Render(wxDC& dc);
 
	DECLARE_EVENT_TABLE()
	
private:
	// Variables here
    std::string mHeader;
    std::map<char, std::pair<std::string, int>> mAcids;
};

