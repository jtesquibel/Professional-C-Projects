//
//  DNADrawPanel.cpp
//  DNAwx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#include "DNADrawPanel.h"
#include <wx/dcclient.h>
#include <wx/sizer.h>
#include <array>
#include <sstream>
#include <iomanip>

BEGIN_EVENT_TABLE(DNADrawPanel, wxPanel)
	EVT_PAINT(DNADrawPanel::PaintEvent)
END_EVENT_TABLE()

DNADrawPanel::DNADrawPanel(wxFrame* parent)
: wxPanel(parent)
{
   
}

void DNADrawPanel::PaintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	Render(dc);
}

void DNADrawPanel::PaintNow()
{
	wxClientDC dc(this);
	Render(dc);
}

void DNADrawPanel::Render(wxDC& dc)
{
	// Clear
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	
	// TODO: Draw histogram, if one has been generated
    
    double total = 0;
    for (auto it = mAcids.begin(); it != mAcids.end(); it++)
    {
        total += it->second.second;
    }
    dc.SetPen(*wxBLACK_PEN);
    dc.SetTextForeground(*wxBLACK);
    dc.DrawText(mHeader, 10, 0);
    int i = 0;
    for (auto it = mAcids.begin(); it != mAcids.end(); it++)
    {
        if (i % 3 == 0)
        {
            dc.SetTextForeground(*wxRED);
            dc.SetBrush(*wxRED_BRUSH);
        }
        else if (i % 3 == 1)
        {
            dc.SetTextForeground(*wxBLUE);
            dc.SetBrush(*wxBLUE_BRUSH);
        }
        else if (i % 3 == 2)
        {
            wxColour green = wxColour(0, 100, 0);
            dc.SetTextForeground(green);
            dc.SetBrush(green);
        }
        std::string text;
        double percent = (it->second.second/total)*100;
        text += it->second.first;
        text += ": ";
        std::ostringstream ss1;
        ss1 << std::setprecision(2) << std::fixed << percent;
        text += ss1.str();
        ss1.clear();
        text += "% (";
        std::ostringstream ss2;
        ss2 << it->second.second;
        text += ss2.str();
        text += ")";
        dc.DrawText(text, 10, 30*i+45);
        dc.DrawRectangle(200, 30*i+40, it->second.second, 30);
        i++;
    }
    dc.SetPen(*wxBLACK_PEN);
    // dc.SetTextForeground(*wxBLACK_PEN);
    dc.SetBrush(*wxRED_BRUSH);
    
    
}

void DNADrawPanel::SetHeader(std::string header)
{
    mHeader = header;
}

void DNADrawPanel::SetAcids(std::map<char, std::pair<std::string, int>> acids)
{
    mAcids = acids;
    this->PaintNow();
}
