#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <fstream>
#include "Op.h"
#include "Exceptions.h"

// Defines state data accessible by the machine and ops
struct MachineState
{
	// Friend Machine so BindState works
	template <typename MachineTraits>
	friend class Machine;

	enum Facing { UP, RIGHT, DOWN, LEFT };
	MachineState()
		: mProgramCounter(1)
		, mActionsTaken(0)
		, mFacing(RIGHT)
		, mTest(false)
        , mXCor(0)
        , mYCor(0)
	{ }

	~MachineState()
	{
	}

	// Active line number in behavior program
	int mProgramCounter;
	// Number of actions taken this turn
	int mActionsTaken;
	// Current facing of this character
	Facing mFacing;
	// Test flag for branches
	bool mTest;
    // X coordinate
    int mXCor;
    // Y Coordinate
    int mYCor;

	int GetActionsPerTurn() const noexcept { return mActionsPerTurn; }
	bool GetInfect() const noexcept { return mInfectOnAttack; }
private:
	// Data which is set by the traits
	int mActionsPerTurn;
	bool mInfectOnAttack;
};

// Describes the machine which processes ops.
// Different policies dictate behavior possible for machine.
template <typename MachineTraits>
class Machine
{
public:
	// Load in all the ops for this machine from the specified file
	void LoadMachine(const std::string& filename);

	// Given the state, binds the trait parameters to it
	void BindState(MachineState& state);

	// Take a turn using this logic for the passed in state
	void TakeTurn(MachineState& state);

	// Destructor
	~Machine();
private:
	std::vector<std::shared_ptr<Op>> mOps;
};

template <typename MachineTraits>
void Machine<MachineTraits>::LoadMachine(const std::string& filename)
{
	// TEMP CODE: Add your parsing code here!
	mOps.clear();
    // mOps.push_back(std::make_shared<OpRotate>(0));
    std::ifstream zomFile(filename);
    
    std::string line;
    while (std::getline(zomFile, line))
    {
        std::string op;
        if (line.find(",") != std::string::npos)
        {
            int param;
            if (line.find(";") != line.npos)
            {
                line = line.substr(0, line.find(";"));
            }
            if (line.find(" ") != std::string::npos)
            {
                line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
            }
            op = line.substr(0, line.find(","));
            // std::cout << "op = " << op << std::endl;
            param = std::stoi(line.substr(line.find(",")+1, line.length()));
            std::cout << "param = " << param << std::endl;
            
            if (op == "rotate")
            {
                mOps.push_back(std::make_shared<OpRotate>(param));
            }
            else if (op == "test_human")
            {
                mOps.push_back(std::make_shared<OpTestHuman>(param));
            }
            else if (op == "test_zombie")
            {
                mOps.push_back(std::make_shared<OpTestZombie>(param));
            }
            else if (op == "je")
            {
                mOps.push_back(std::make_shared<OpJE>(param));
            }
            else if (op == "jne")
            {
                mOps.push_back(std::make_shared<OpJNE>(param));
            }
            else if (op == "goto")
            {
                mOps.push_back(std::make_shared<OpGoTo>(param));
            }

        }
        else
        {
            if (line.find(";") != std::string::npos)
            {
                line = line.substr(0, line.find(";"));
            }
            if (line.find(" ") != std::string::npos)
            {
                line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
            }
            op = line;
            // std::cout << "op = " << op << std::endl;
            // std::cout << "param = none" << std::endl;
            
            if (op == "attack")
            {
                mOps.push_back(std::make_shared<OpAttack>(0));
            }
            else if (op == "ranged_attack")
            {
                mOps.push_back(std::make_shared<OpRangedAttack>(0));
            }
            
            else if (op == "forward")
            {
                mOps.push_back(std::make_shared<OpForward>(0));
            }
            else if (op == "end_turn")
            {
                mOps.push_back(std::make_shared<OpEndTurn>(0));
            }
            else if (op == "test_wall")
            {
                mOps.push_back(std::make_shared<OpTestWall>(0));
            }
            else if (op == "test_random")
            {
                mOps.push_back(std::make_shared<OpTestRandom>(0));
            }
            else if (op == "test_passable")
            {
                mOps.push_back(std::make_shared<OpTestPassable>(0));
            }
        }
        
        
        
        
        
        
    }
}

template <typename MachineTraits>
void Machine<MachineTraits>::BindState(MachineState& state)
{
	state.mActionsPerTurn = MachineTraits::ACTIONS_PER_TURN;
	state.mInfectOnAttack = MachineTraits::INFECT_ON_ATTACK;
}

template <typename MachineTraits>
void Machine<MachineTraits>::TakeTurn(MachineState& state)
{
	std::cout << "TAKING TURN" << std::endl;
	state.mActionsTaken = 0;
	while (state.mActionsTaken < MachineTraits::ACTIONS_PER_TURN)
	{
		mOps.at(state.mProgramCounter - 1)->Execute(state);
	}
}

template <typename MachineTraits>
Machine<MachineTraits>::~Machine()
{
	mOps.clear();
}
