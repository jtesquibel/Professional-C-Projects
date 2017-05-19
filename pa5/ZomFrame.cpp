//
//  ZomFrame.cpp
//  zombiewx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#include "ZomFrame.h"
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include <iterator>
#include "ZomDrawPanel.h"

enum
{
	ID_SImSTART=1000,
    ID_LOAD_ZOMBIES=1001,
    ID_LOAD_SURVIVORS=1002,
    ID_RANDOMIZE=1003,
    ID_RESET=1004,
	ID_TURN_TIMER,
};

wxBEGIN_EVENT_TABLE(ZomFrame, wxFrame)
	EVT_MENU(wxID_EXIT, ZomFrame::OnExit)
	EVT_MENU(wxID_NEW, ZomFrame::OnNew)
	EVT_MENU(ID_SImSTART, ZomFrame::OnSimStart)
    EVT_MENU(ID_LOAD_ZOMBIES, ZomFrame::OnLoadZombies)
    EVT_MENU(ID_LOAD_SURVIVORS, ZomFrame::OnLoadSurvivors)
    EVT_MENU(ID_RANDOMIZE, ZomFrame::OnRandomize)
    EVT_MENU(ID_RESET, ZomFrame::OnReset)
	EVT_TIMER(ID_TURN_TIMER, ZomFrame::OnTurnTimer)
wxEND_EVENT_TABLE()

ZomFrame::ZomFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
, mIsActive(false)
{
	// File menu
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_NEW);
	menuFile->Append(wxID_EXIT);
	
	// Simulation menu
	mSimMenu = new wxMenu;
	mSimMenu->Append(ID_SImSTART, "Start/stop\tSpace", "Start or stop the simulation");
    mSimMenu->Append(ID_LOAD_ZOMBIES, "Load Zombies");
    mSimMenu->Append(ID_LOAD_SURVIVORS, "Load Survivors");
    mSimMenu->Append(ID_RANDOMIZE, "Randomize");
    mSimMenu->Append(ID_RESET, "Reset");
	
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(mSimMenu, "&Simulation");
	SetMenuBar(menuBar);
	CreateStatusBar();
	
	// Prepare the draw panel and show this frame
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	mPanel = new ZomDrawPanel(this);
	sizer->Add(mPanel, 1, wxEXPAND);
	
	SetSizer(sizer);
	SetAutoLayout(true);
	Show(true);
	
	mTurnTimer = new wxTimer(this, ID_TURN_TIMER);

	// TEMP CODE: Initialize zombie test machine
	// zombieMachine.LoadMachine(std::string(""));
	// zombieMachine.BindState(zombieTestState);
	// END TEMP CODE
}

ZomFrame::~ZomFrame()
{
	delete mTurnTimer;
}

void ZomFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void ZomFrame::OnNew(wxCommandEvent& event)
{
	// TODO: Add code for File>New

    mTurnTimer->Stop();
    World::get().mZombieStates.clear();
    World::get().mHumanStates.clear();
    World::get().mZombieMachines.clear();
    World::get().mHumanMachines.clear();
    mPanel->PaintNow();
}

void ZomFrame::OnReset(wxCommandEvent &event)
{

    mTurnTimer->Stop();
    World::get().mZombieStates.clear();
    World::get().mHumanStates.clear();
    World::get().mZombieMachines.clear();
    World::get().mHumanMachines.clear();
    mPanel->PaintNow();
}

void ZomFrame::OnSimStart(wxCommandEvent& event)
{
	if (!mIsActive)
	{
		// Add timer to run once per second
		mTurnTimer->Start(1000);
		mIsActive = true;
	}
	else
	{
		mTurnTimer->Stop();
		mIsActive = false;
	}
}

void ZomFrame::OnLoadZombies(wxCommandEvent &event)
{
    wxFileDialog* openDialog =
    new wxFileDialog( this, _("Choose a file to open"), "", "", _("ZOM Files (*.zom)|*.zom"),
                     wxFD_OPEN, wxDefaultPosition);
    
    if ( openDialog->ShowModal() == wxID_OK )
    {
        World::get().mZombieFileName = std::string(openDialog->GetPath().mb_str());
        std::shared_ptr<Machine<ZombieTraits>> m = std::make_shared<Machine<ZombieTraits>>();
        std::shared_ptr<MachineState> state = std::make_shared<MachineState>();
        m->LoadMachine(std::string(openDialog->GetPath().mb_str()));
        m->BindState(*state);
        World::get().mZombieMachines.push_back(m);
        World::get().mZombieStates.push_back(state);
        
        mPanel->PaintNow();
    }
}

void ZomFrame::OnLoadSurvivors(wxCommandEvent &event)
{
    wxFileDialog* openDialog =
    new wxFileDialog( this, _("Choose a file to open"), "", "", _("ZOM Files (*.zom)|*.zom"),
                     wxFD_OPEN, wxDefaultPosition);
    
    if ( openDialog->ShowModal() == wxID_OK )
    {
        World::get().mHumanFileName = std::string(openDialog->GetPath().mb_str());
        mFileName = std::string(openDialog->GetPath().mb_str());
        std::shared_ptr<Machine<HumanTraits>> m = std::make_shared<Machine<HumanTraits>>();
        std::shared_ptr<MachineState> state = std::make_shared<MachineState>();
        m->LoadMachine(std::string(openDialog->GetPath().mb_str()));
        m->BindState(*state);
        World::get().mHumanMachines.push_back(m);
        World::get().mHumanStates.push_back(state);
        
        mPanel->PaintNow();
    }
}

void ZomFrame::OnTurnTimer(wxTimerEvent& event)
{
    World::get().mTurns++;
    std::vector<std::shared_ptr<Machine<ZombieTraits>>>::iterator it; // = World::get().mZombieMachines.end();
    std::vector<std::shared_ptr<MachineState>>::iterator itt;
    for (it = World::get().mZombieMachines.begin(), itt = World::get().mZombieStates.begin(); it != World::get().mZombieMachines.end(); it++, itt++)
    {
        (*it)->TakeTurn(*(*itt));
        mPanel->PaintNow();
    }
    
    std::vector<std::shared_ptr<Machine<HumanTraits>>>::iterator it2; // = World::get().mZombieMachines.end();
    std::vector<std::shared_ptr<MachineState>>::iterator itt2;
    for (it2 = World::get().mHumanMachines.begin(), itt2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanMachines.end(); it2++, itt2++)
    {
        (*it2)->TakeTurn(*(*itt2));
        mPanel->PaintNow();
    }

}

void ZomFrame::OnRandomize(wxCommandEvent &event)
{
    OnRandomizeZombies();
    OnRandomizeHumans();
}

void ZomFrame::OnRandomizeZombies()
{
    for (int i = 0; i < 19; i++)
    {
        std::shared_ptr<Machine<ZombieTraits>> m = std::make_shared<Machine<ZombieTraits>>();
        // srand(static_cast<unsigned>(time(NULL)));
        int x = rand() % 19;
        int y = rand() % 19;
        std::shared_ptr<MachineState> state = std::make_shared<MachineState>();
        state->mXCor = x;
        state->mYCor = y;
        m->LoadMachine(World::get().mZombieFileName);
        m->BindState(*state);
        World::get().mZombieMachines.push_back(m);
        World::get().mZombieStates.push_back(state);
    }
    
    mPanel->PaintNow();
}

void ZomFrame::OnRandomizeHumans()
{
    for (int i = 0; i < 9; i++)
    {
        std::shared_ptr<Machine<HumanTraits>> m = std::make_shared<Machine<HumanTraits>>();
        // srand(static_cast<unsigned>(time(NULL)));
        int x = rand() % 19;
        int y = rand() % 19;
        std::shared_ptr<MachineState> state = std::make_shared<MachineState>();
        state->mXCor = x;
        state->mYCor = y;
        m->LoadMachine(World::get().mHumanFileName);
        m->BindState(*state);
        World::get().mHumanMachines.push_back(m);
        World::get().mHumanStates.push_back(state);
    }
    
    mPanel->PaintNow();
}
