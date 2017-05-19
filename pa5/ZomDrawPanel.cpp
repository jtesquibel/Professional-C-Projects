//
//  ZomDrawPanel.cpp
//  zombiewx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#include "ZomDrawPanel.h"
#include <wx/dcclient.h>
#include <wx/sizer.h>
#include "Machine.h"
#include "World.hpp"

BEGIN_EVENT_TABLE(ZomDrawPanel, wxPanel)
	EVT_PAINT(ZomDrawPanel::PaintEvent)
END_EVENT_TABLE()

ZomDrawPanel::ZomDrawPanel(wxFrame* parent)
: wxPanel(parent)
{
	
}

void ZomDrawPanel::PaintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	Render(dc);
}

void ZomDrawPanel::PaintNow()
{
	wxClientDC dc(this);
	Render(dc);
}

void ZomDrawPanel::Render(wxDC& dc)
{
	// Clear
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	
	// Draw the grid
	DrawGrid(dc);
    
    DrawZombies(dc);
    DrawHumans(dc);
    DrawStats(dc);
}

void ZomDrawPanel::DrawGrid(wxDC& dc)
{
	dc.SetPen(*wxBLACK_PEN);
	dc.DrawRectangle(10, 10, 600, 600);
    for (int i = 0; i < 20; i++)
    {
        dc.DrawLine(0+10, i*30+10, 600+10, i*30+10);
        dc.DrawLine(i*30+10, 0+10, i*30+10, 600+10);
    }
    
    dc.SetPen(*wxRED_PEN);
    

    
}

void ZomDrawPanel::DrawZombies(wxDC& dc)
{
    std::vector<std::shared_ptr<MachineState>>::iterator it;
    dc.SetBrush(*wxRED_BRUSH);
    for (it = World::get().mZombieStates.begin(); it != World::get().mZombieStates.end(); it++)
    {
        wxPointList list;
        if ((*it)->mFacing == MachineState::UP)
        {
            wxPoint p = wxPoint((*it)->mXCor*30+25, (*it)->mYCor*30+10);
            list.Append(&p);
            wxPoint p2 = wxPoint((*it)->mXCor*30+10, (*it)->mYCor*30+40);
            list.Append(&p2);
            wxPoint p3 = wxPoint((*it)->mXCor*30+40, (*it)->mYCor*30+40);
            list.Append(&p3);
            dc.DrawPolygon(&list);
        }
        else if ((*it)->mFacing == MachineState::DOWN)
        {
            wxPoint p = wxPoint((*it)->mXCor*30+25, (*it)->mYCor*30+40);
            list.Append(&p);
            wxPoint p2 = wxPoint((*it)->mXCor*30+10, (*it)->mYCor*30+10);
            list.Append(&p2);
            wxPoint p3 = wxPoint((*it)->mXCor*30+40, (*it)->mYCor*30+10);
            list.Append(&p3);
            dc.DrawPolygon(&list);
        }
        else if ((*it)->mFacing == MachineState::LEFT)
        {
            wxPoint p = wxPoint((*it)->mXCor*30+10, (*it)->mYCor*30+25);
            list.Append(&p);
            wxPoint p2 = wxPoint((*it)->mXCor*30+40, (*it)->mYCor*30+10);
            list.Append(&p2);
            wxPoint p3 = wxPoint((*it)->mXCor*30+40, (*it)->mYCor*30+40);
            list.Append(&p3);
            dc.DrawPolygon(&list);
        }
        else if ((*it)->mFacing == MachineState::RIGHT)
        {
            wxPoint p = wxPoint((*it)->mXCor*30+40, (*it)->mYCor*30+25);
            list.Append(&p);
            wxPoint p2 = wxPoint((*it)->mXCor*30+10, (*it)->mYCor*30+10);
            list.Append(&p2);
            wxPoint p3 = wxPoint((*it)->mXCor*30+10, (*it)->mYCor*30+40);
            list.Append(&p3);
            dc.DrawPolygon(&list);
        }
        
        
    }
    
}

void ZomDrawPanel::DrawHumans(wxDC& dc)
{
    std::vector<std::shared_ptr<MachineState>>::iterator it;
    dc.SetPen(*wxGREEN_PEN);
    dc.SetBrush(*wxGREEN_BRUSH);
    for (it = World::get().mHumanStates.begin(); it != World::get().mHumanStates.end(); it++)
    {
        wxPointList list;
        if ((*it)->mFacing == MachineState::UP)
        {
            wxPoint p = wxPoint((*it)->mXCor*30+25, (*it)->mYCor*30+10);
            list.Append(&p);
            wxPoint p2 = wxPoint((*it)->mXCor*30+10, (*it)->mYCor*30+40);
            list.Append(&p2);
            wxPoint p3 = wxPoint((*it)->mXCor*30+40, (*it)->mYCor*30+40);
            list.Append(&p3);
            dc.DrawPolygon(&list);
        }
        else if ((*it)->mFacing == MachineState::DOWN)
        {
            wxPoint p = wxPoint((*it)->mXCor*30+25, (*it)->mYCor*30+40);
            list.Append(&p);
            wxPoint p2 = wxPoint((*it)->mXCor*30+10, (*it)->mYCor*30+10);
            list.Append(&p2);
            wxPoint p3 = wxPoint((*it)->mXCor*30+40, (*it)->mYCor*30+10);
            list.Append(&p3);
            dc.DrawPolygon(&list);
        }
        else if ((*it)->mFacing == MachineState::LEFT)
        {
            wxPoint p = wxPoint((*it)->mXCor*30+10, (*it)->mYCor*30+25);
            list.Append(&p);
            wxPoint p2 = wxPoint((*it)->mXCor*30+40, (*it)->mYCor*30+10);
            list.Append(&p2);
            wxPoint p3 = wxPoint((*it)->mXCor*30+40, (*it)->mYCor*30+40);
            list.Append(&p3);
            dc.DrawPolygon(&list);
        }
        else if ((*it)->mFacing == MachineState::RIGHT)
        {
            wxPoint p = wxPoint((*it)->mXCor*30+40, (*it)->mYCor*30+25);
            list.Append(&p);
            wxPoint p2 = wxPoint((*it)->mXCor*30+10, (*it)->mYCor*30+10);
            list.Append(&p2);
            wxPoint p3 = wxPoint((*it)->mXCor*30+10, (*it)->mYCor*30+40);
            list.Append(&p3);
            dc.DrawPolygon(&list);
        }
        
        
    }
    
}

void ZomDrawPanel::DrawStats(wxDC &dc)
{
    dc.SetPen(*wxRED_PEN);
    dc.SetBrush(*wxWHITE_BRUSH);
    // dc.DrawRectangle(620, 10, 160, 80);
    dc.DrawText("Zombies", 620, 10);
    dc.DrawText("Program: ", 620, 40);
    if (World::get().mZombieFileName != "none")
    {
        size_t lastindex = World::get().mZombieFileName.find_last_of("/");
        wxString extension = World::get().mZombieFileName.substr(lastindex+1, World::get().mZombieFileName.length());
        dc.DrawText(extension, 680, 40);
    }
    wxString b = wxString::Format(wxT("%ld"),World::get().mZombieMachines.size());
    dc.DrawText("Alive:", 620, 70);
    dc.DrawText(b, 660, 70);
    
    dc.SetPen(*wxGREEN_PEN);
    dc.DrawText("Humans", 620, 130);
    dc.DrawText("Program: ", 620, 160);
    if (World::get().mHumanFileName != "none")
    {
        size_t lastindex = World::get().mHumanFileName.find_last_of("/");
        wxString extension = World::get().mHumanFileName.substr(lastindex+1, World::get().mZombieFileName.length());
        dc.DrawText(extension, 680, 160);
    }
    wxString c = wxString::Format(wxT("%ld"),World::get().mHumanMachines.size());
    dc.DrawText("Alive:", 620, 190);
    dc.DrawText(c, 660, 190);
    
    dc.DrawText("Month: ", 620, 230);
    wxString d = wxString::Format(wxT("%i"),World::get().mTurns);
    dc.DrawText(d, 670, 230);
    
    
}

