#include "Op.h"
#include "Machine.h"
#include "ZomDrawPanel.h"
#include "World.hpp"
#include <iostream>

// Output state information for debugging purposes
void Op::DebugOutput(MachineState& state)
{
	std::cout << state.mProgramCounter << ":" << mOpName << "," << mParam << std::endl;
    std::cout << "[" << state.mXCor << ", " << state.mYCor << "]" << std::endl;
    std::cout << "prog count = " << state.mProgramCounter << std::endl;
}

void OpRotate::Execute(MachineState& state)
{
	DebugOutput(state);
	switch (state.mFacing)
	{
	case (MachineState::UP) :
		if (mParam == 0)
		{
			state.mFacing = MachineState::RIGHT;
		}
		else
		{
			state.mFacing = MachineState::LEFT;
		}
		break;
	case (MachineState::RIGHT) :
		if (mParam == 0)
		{
			state.mFacing = MachineState::DOWN;
		}
		else
		{
			state.mFacing = MachineState::UP;
		}
		break;
	case (MachineState::DOWN) :
		if (mParam == 0)
		{
			state.mFacing = MachineState::LEFT;
		}
		else
		{
			state.mFacing = MachineState::RIGHT;
		}
		break;
	default:
	case (MachineState::LEFT) :
		if (mParam == 0)
		{
			state.mFacing = MachineState::UP;
		}
		else
		{
			state.mFacing = MachineState::DOWN;
		}
		break;
	}

	/*std::cout << "Now facing ";
	switch (state.mFacing)
	{
	case (MachineState::UP):
		std::cout << "UP";
		break;
	case (MachineState::RIGHT):
		std::cout << "RIGHT";
		break;
	case (MachineState::DOWN):
		std::cout << "DOWN";
		break;
	case (MachineState::LEFT):
		std::cout << "LEFT";
		break;
	}
	std::cout << std::endl;*/
	state.mProgramCounter++;
	state.mActionsTaken++;
    
}

void OpGoTo::Execute(MachineState& state)
{
	DebugOutput(state);
	state.mProgramCounter = mParam;
  
}

void OpTestWall::Execute(MachineState& state)
{
    DebugOutput(state);
    switch (state.mFacing)
    {
        case (MachineState::UP) :
            if (state.mYCor == 0)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
            break;
        case (MachineState::RIGHT) :
            if (state.mXCor == 19)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
            break;
        case (MachineState::DOWN) :
            if (state.mYCor == 19)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
            break;
        default:
        case (MachineState::LEFT) :
            if (state.mXCor == 0)
            {
                state.mTest = true;
            }
            else
            {
                state.mTest = false;
            }
            break;
    }
    
    state.mProgramCounter++;

}

void OpJE::Execute(MachineState& state)
{
    DebugOutput(state);
    // need to throw exception if n is bad
    if (state.mTest == true)
    {
        std::cout << "mparam = " << mParam << std::endl;
        state.mProgramCounter = mParam;
    }
    else
    {
        std::cout << "mparam = " << mParam << std::endl;
        state.mProgramCounter++;
    }

    // std::cout << "prog count = " << state.mProgramCounter << std::endl;
}

void OpForward::Execute(MachineState& state)
{
    DebugOutput(state);
    std::vector<std::shared_ptr<MachineState>>::iterator it;
    std::vector<std::shared_ptr<MachineState>>::iterator it2;
    bool works = true;
    switch (state.mFacing)
    {
        case (MachineState::UP) :
            if (state.mYCor == 0) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(); it != World::get().mZombieStates.end(); it++)
                {
                    if (state.mYCor-1 == (*it)->mYCor && state.mXCor == (*it)->mXCor)
                    {
                        works = false;
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mYCor-1 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        works = false;
                        break;
                    }
                }
                if (works == true)
                {
                    state.mYCor--;
                }
                
            }
            break;
        case (MachineState::RIGHT) :
            if (state.mXCor == 19) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(); it != World::get().mZombieStates.end(); it++)
                {
                    if (state.mXCor+1 == (*it)->mXCor && state.mYCor == (*it)->mYCor)
                    {
                        works = false;
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mXCor+1 == (*it2)->mXCor && state.mYCor == (*it2)->mYCor)
                    {
                        works = false;
                        break;
                    }
                }
                if (works == true)
                {
                    state.mXCor++;
                }
            }
            break;
        case (MachineState::DOWN) :
            if (state.mYCor == 19) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(); it != World::get().mZombieStates.end(); it++)
                {
                    if (state.mYCor+1 == (*it)->mYCor && state.mXCor == (*it)->mXCor)
                    {
                        works = false;
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mYCor+1 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        works = false;
                        break;
                    }
                }
                if (works == true)
                {
                    state.mYCor++;
                }
            }
            break;
        default:
        case (MachineState::LEFT) :
            if (state.mXCor == 0) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(); it != World::get().mZombieStates.end(); it++)
                {
                    if (state.mXCor-1 == (*it)->mXCor && state.mYCor == (*it)->mYCor)
                    {
                        works = false;
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mXCor-1 == (*it2)->mXCor && state.mYCor == (*it2)->mYCor)
                    {
                        works = false;
                        break;
                    }
                }
                if (works == true)
                {
                    state.mXCor--;
                }
            }
            break;
    }
    state.mProgramCounter++;
    state.mActionsTaken++;
}

void OpTestRandom::Execute(MachineState& state)
{
    DebugOutput(state);
    // randomly set flag to true or false
    // srand(static_cast<unsigned>(time(NULL)));
    //int r = rand() % 2;
    int r = ((double) rand() / (RAND_MAX)) + 1;
    if (r == 0)
    {
        state.mTest = true;
    }
    else if (r == 1)
    {
        state.mTest = false;
    }
    state.mProgramCounter++;
    
}

void OpEndTurn::Execute(MachineState& state)
{
    DebugOutput(state);
    // end turn
    // state.mActionsTaken++;
    
}

void OpTestHuman::Execute(MachineState& state)
{
    DebugOutput(state);
    
    std::vector<std::shared_ptr<MachineState>>::iterator it2;
    bool human = false;
    switch (state.mFacing)
    {
        case (MachineState::UP) :
            if (state.mYCor == 0) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mYCor-1 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        human = true;
                        break;
                    }
                }
                if (human == true)
                {
                    state.mTest = true;
                }
                else if (human == false)
                {
                    state.mTest = false;
                }
                
            }
            break;
        case (MachineState::RIGHT) :
            if (state.mXCor == 19) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mYCor-1 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        human = true;
                        break;
                    }
                }
                if (human == true)
                {
                    state.mTest = true;
                }
                else if (human == false)
                {
                    state.mTest = false;
                }            }
            break;
        case (MachineState::DOWN) :
            if (state.mYCor == 19) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mYCor-1 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        human = true;
                        break;
                    }
                }
                if (human == true)
                {
                    state.mTest = true;
                }
                else if (human == false)
                {
                    state.mTest = false;
                }            }
            break;
        default:
        case (MachineState::LEFT) :
            if (state.mXCor == 0) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mYCor-1 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        human = true;
                        break;
                    }
                }
                if (human == true)
                {
                    state.mTest = true;
                }
                else if (human == false)
                {
                    state.mTest = false;
                }            }
            break;
    }
    state.mProgramCounter++;

}

void OpTestZombie::Execute(MachineState& state)
{
    DebugOutput(state);
    
    std::vector<std::shared_ptr<MachineState>>::iterator it2;
    bool zombie = false;
    switch (state.mFacing)
    {
        case (MachineState::UP) :
            if (state.mYCor == 0) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mYCor-1 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        zombie = true;
                        break;
                    }
                }
                if (zombie == true)
                {
                    state.mTest = true;
                }
                else if (zombie == false)
                {
                    state.mTest = false;
                }
                
            }
            break;
        case (MachineState::RIGHT) :
            if (state.mXCor == 19) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mYCor-1 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        zombie = true;
                        break;
                    }
                }
                if (zombie == true)
                {
                    state.mTest = true;
                }
                else if (zombie == false)
                {
                    state.mTest = false;
                }            }
            break;
        case (MachineState::DOWN) :
            if (state.mYCor == 19) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mYCor-1 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        zombie = true;
                        break;
                    }
                }
                if (zombie == true)
                {
                    state.mTest = true;
                }
                else if (zombie == false)
                {
                    state.mTest = false;
                }            }
            break;
        default:
        case (MachineState::LEFT) :
            if (state.mXCor == 0) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mYCor-1 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        zombie = true;
                        break;
                    }
                }
                if (zombie == true)
                {
                    state.mTest = true;
                }
                else if (zombie == false)
                {
                    state.mTest = false;
                }
            }
            break;
    }
    state.mProgramCounter++;
  
}

void OpTestPassable::Execute(MachineState& state)
{
    DebugOutput(state);
    std::vector<std::shared_ptr<MachineState>>::iterator it;
    std::vector<std::shared_ptr<MachineState>>::iterator it2;
    bool works = true;
    switch (state.mFacing)
    {
        case (MachineState::UP) :
            if (state.mYCor == 0) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(); it != World::get().mZombieStates.end(); it++)
                {
                    if (state.mYCor-1 == (*it)->mYCor && state.mXCor == (*it)->mXCor)
                    {
                        works = false;
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mYCor-1 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        works = false;
                        break;
                    }
                }
                if (works == true)
                {
                    state.mTest = true;
                }
                else if (works == false)
                {
                    state.mTest = false;
                }
                
            }
            break;
        case (MachineState::RIGHT) :
            if (state.mXCor == 19) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(); it != World::get().mZombieStates.end(); it++)
                {
                    if (state.mXCor+1 == (*it)->mXCor && state.mYCor == (*it)->mYCor)
                    {
                        works = false;
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mXCor+1 == (*it2)->mXCor && state.mYCor == (*it2)->mYCor)
                    {
                        works = false;
                        break;
                    }
                }
                if (works == true)
                {
                    state.mTest = true;
                }
                else if (works == false)
                {
                    state.mTest = false;
                }
            }
            break;
        case (MachineState::DOWN) :
            if (state.mYCor == 19) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(); it != World::get().mZombieStates.end(); it++)
                {
                    if (state.mYCor+1 == (*it)->mYCor && state.mXCor == (*it)->mXCor)
                    {
                        works = false;
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mYCor+1 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        works = false;
                        break;
                    }
                }
                if (works == true)
                {
                    state.mTest = true;
                }
                else if (works == false)
                {
                    state.mTest = false;
                }
            }
            break;
        default:
        case (MachineState::LEFT) :
            if (state.mXCor == 0) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(); it != World::get().mZombieStates.end(); it++)
                {
                    if (state.mXCor-1 == (*it)->mXCor && state.mYCor == (*it)->mYCor)
                    {
                        works = false;
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(); it2 != World::get().mHumanStates.end(); it2++)
                {
                    if (state.mXCor-1 == (*it2)->mXCor && state.mYCor == (*it2)->mYCor)
                    {
                        works = false;
                        break;
                    }
                }
                if (works == true)
                {
                    state.mTest = true;
                }
                else if (works == false)
                {
                    state.mTest = false;
                }
            }
            break;
    }

    state.mProgramCounter++;
    
}

void OpJNE::Execute(MachineState& state)
{
    DebugOutput(state);
    // need to throw exception if n is bad
    if (state.mTest == false)
    {
        state.mProgramCounter = mParam;
    }
    else
    {
        state.mProgramCounter++;
    }

}

void OpAttack::Execute(MachineState& state)
{
    DebugOutput(state);
    std::vector<std::shared_ptr<MachineState>>::iterator it;
    std::vector<std::shared_ptr<MachineState>>::iterator it2;
    std::vector<std::shared_ptr<Machine<ZombieTraits>>>::iterator itt;
    std::vector<std::shared_ptr<Machine<HumanTraits>>>::iterator itt2;
    bool works = true;
    bool zombie = false;
    bool human = false;
    switch (state.mFacing)
    {
        case (MachineState::UP) :
            if (state.mYCor == 0) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(), itt = World::get().mZombieMachines.begin(); it != World::get().mZombieStates.end(); it++, itt++)
                {
                    if (state.mYCor-1 == (*it)->mYCor && state.mXCor == (*it)->mXCor)
                    {
                        works = false;
                        zombie = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mZombieStates.erase(it);
                            World::get().mZombieMachines.erase(itt);
                        }
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(), itt2 = World::get().mHumanMachines.begin(); it2 != World::get().mHumanStates.end(); it2++, itt2++)
                {
                    if (state.mYCor-1 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        works = false;
                        human = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                            int humX = (*it2)->mXCor;
                            int humY = (*it2)->mYCor;
                            World::get().mHumanStates.erase(it2);
                            World::get().mHumanMachines.erase(itt2);
                            std::shared_ptr<Machine<ZombieTraits>> m = std::make_shared<Machine<ZombieTraits>>();
                            // srand(static_cast<unsigned>(time(NULL)));
                            std::shared_ptr<MachineState> state = std::make_shared<MachineState>();
                            state->mXCor = humX;
                            state->mYCor = humY;
                            m->LoadMachine(World::get().mZombieFileName);
                            m->BindState(*state);
                            World::get().mZombieMachines.push_back(m);
                            World::get().mZombieStates.push_back(state);

                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mHumanStates.erase(it2);
                            World::get().mHumanMachines.erase(itt2);
                        }
                        break;
                    }
                }
                
            }
            break;
        case (MachineState::RIGHT) :
            if (state.mXCor == 19) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(), itt = World::get().mZombieMachines.begin(); it != World::get().mZombieStates.end(); it++, itt++)
                {
                    if (state.mXCor+1 == (*it)->mXCor && state.mYCor == (*it)->mYCor)
                    {
                        works = false;
                        zombie = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mZombieStates.erase(it);
                            World::get().mZombieMachines.erase(itt);
                        }
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(), itt2 = World::get().mHumanMachines.begin(); it2 != World::get().mHumanStates.end(); it2++, itt2++)
                {
                    if (state.mXCor+1 == (*it2)->mXCor && state.mYCor == (*it2)->mYCor)
                    {
                        works = false;
                        human = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                            int humX = (*it2)->mXCor;
                            int humY = (*it2)->mYCor;
                            World::get().mHumanStates.erase(it2);
                            World::get().mHumanMachines.erase(itt2);
                            std::shared_ptr<Machine<ZombieTraits>> m = std::make_shared<Machine<ZombieTraits>>();
                            // srand(static_cast<unsigned>(time(NULL)));
                            std::shared_ptr<MachineState> state = std::make_shared<MachineState>();
                            state->mXCor = humX;
                            state->mYCor = humY;
                            m->LoadMachine(World::get().mZombieFileName);
                            m->BindState(*state);
                            World::get().mZombieMachines.push_back(m);
                            World::get().mZombieStates.push_back(state);
                            
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mHumanStates.erase(it2);
                            World::get().mHumanMachines.erase(itt2);
                        }

                        break;
                    }
                }

            }
            break;
        case (MachineState::DOWN) :
            if (state.mYCor == 19) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(), itt = World::get().mZombieMachines.begin(); it != World::get().mZombieStates.end(); it++, itt++)
                {
                    if (state.mYCor+1 == (*it)->mYCor && state.mXCor == (*it)->mXCor)
                    {
                        works = false;
                        zombie = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mZombieStates.erase(it);
                            World::get().mZombieMachines.erase(itt);
                        }
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(), itt2 = World::get().mHumanMachines.begin(); it2 != World::get().mHumanStates.end(); it2++, itt2++)
                {
                    if (state.mYCor+1 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        works = false;
                        human = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                            int humX = (*it2)->mXCor;
                            int humY = (*it2)->mYCor;
                            World::get().mHumanStates.erase(it2);
                            World::get().mHumanMachines.erase(itt2);
                            std::shared_ptr<Machine<ZombieTraits>> m = std::make_shared<Machine<ZombieTraits>>();
                            // srand(static_cast<unsigned>(time(NULL)));
                            std::shared_ptr<MachineState> state = std::make_shared<MachineState>();
                            state->mXCor = humX;
                            state->mYCor = humY;
                            m->LoadMachine(World::get().mZombieFileName);
                            m->BindState(*state);
                            World::get().mZombieMachines.push_back(m);
                            World::get().mZombieStates.push_back(state);
                            
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mHumanStates.erase(it2);
                            World::get().mHumanMachines.erase(itt2);
                        }

                        break;
                    }
                }
//                if (works == true)
//                {
//                    state.mTest = true;
//                }
//                else if (works == false)
//                {
//                    state.mTest = false;
//                }
            }
            break;
        default:
        case (MachineState::LEFT) :
            if (state.mXCor == 0) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(), itt = World::get().mZombieMachines.begin(); it != World::get().mZombieStates.end(); it++, itt++)
                {
                    if (state.mXCor-1 == (*it)->mXCor && state.mYCor == (*it)->mYCor)
                    {
                        works = false;
                        zombie = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mZombieStates.erase(it);
                            World::get().mZombieMachines.erase(itt);
                        }
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(), itt2 = World::get().mHumanMachines.begin(); it2 != World::get().mHumanStates.end(); it2++, itt2++)
                {
                    if (state.mXCor-1 == (*it2)->mXCor && state.mYCor == (*it2)->mYCor)
                    {
                        works = false;
                        human = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                            int humX = (*it2)->mXCor;
                            int humY = (*it2)->mYCor;
                            World::get().mHumanStates.erase(it2);
                            World::get().mHumanMachines.erase(itt2);
                            std::shared_ptr<Machine<ZombieTraits>> m = std::make_shared<Machine<ZombieTraits>>();
                            // srand(static_cast<unsigned>(time(NULL)));
                            std::shared_ptr<MachineState> state = std::make_shared<MachineState>();
                            state->mXCor = humX;
                            state->mYCor = humY;
                            m->LoadMachine(World::get().mZombieFileName);
                            m->BindState(*state);
                            World::get().mZombieMachines.push_back(m);
                            World::get().mZombieStates.push_back(state);
                            
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mHumanStates.erase(it2);
                            World::get().mHumanMachines.erase(itt2);
                        }

                        break;
                    }
                }

            }
            break;
    }

    state.mActionsTaken++;
    
}

void OpRangedAttack::Execute(MachineState& state)
{
    DebugOutput(state);
    std::vector<std::shared_ptr<MachineState>>::iterator it;
    std::vector<std::shared_ptr<MachineState>>::iterator it2;
    std::vector<std::shared_ptr<Machine<ZombieTraits>>>::iterator itt;
    std::vector<std::shared_ptr<Machine<HumanTraits>>>::iterator itt2;
    bool works = true;
    bool zombie = false;
    bool human = false;
    switch (state.mFacing)
    {
        case (MachineState::UP) :
            if (state.mYCor == 0) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(), itt = World::get().mZombieMachines.begin(); it != World::get().mZombieStates.end(); it++, itt++)
                {
                    if (state.mYCor-2 == (*it)->mYCor && state.mXCor == (*it)->mXCor)
                    {
                        works = false;
                        zombie = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mZombieStates.erase(it);
                            World::get().mZombieMachines.erase(itt);
                        }
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(), itt2 = World::get().mHumanMachines.begin(); it2 != World::get().mHumanStates.end(); it2++, itt2++)
                {
                    if (state.mYCor-2 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        works = false;
                        human = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                            
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mHumanStates.erase(it2);
                            World::get().mHumanMachines.erase(itt2);
                        }
                        break;
                    }
                }
                
            }
            break;
        case (MachineState::RIGHT) :
            if (state.mXCor == 19) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(), itt = World::get().mZombieMachines.begin(); it != World::get().mZombieStates.end(); it++, itt++)
                {
                    if (state.mXCor+2 == (*it)->mXCor && state.mYCor == (*it)->mYCor)
                    {
                        works = false;
                        zombie = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mZombieStates.erase(it);
                            World::get().mZombieMachines.erase(itt);
                        }
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(), itt2 = World::get().mHumanMachines.begin(); it2 != World::get().mHumanStates.end(); it2++, itt2++)
                {
                    if (state.mXCor+2 == (*it2)->mXCor && state.mYCor == (*it2)->mYCor)
                    {
                        works = false;
                        human = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                            
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mHumanStates.erase(it2);
                            World::get().mHumanMachines.erase(itt2);
                        }
                        
                        break;
                    }
                }
                
            }
            break;
        case (MachineState::DOWN) :
            if (state.mYCor == 19) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(), itt = World::get().mZombieMachines.begin(); it != World::get().mZombieStates.end(); it++, itt++)
                {
                    if (state.mYCor+2 == (*it)->mYCor && state.mXCor == (*it)->mXCor)
                    {
                        works = false;
                        zombie = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mZombieStates.erase(it);
                            World::get().mZombieMachines.erase(itt);
                        }
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(), itt2 = World::get().mHumanMachines.begin(); it2 != World::get().mHumanStates.end(); it2++, itt2++)
                {
                    if (state.mYCor+2 == (*it2)->mYCor && state.mXCor == (*it2)->mXCor)
                    {
                        works = false;
                        human = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                            
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mHumanStates.erase(it2);
                            World::get().mHumanMachines.erase(itt2);
                        }
                        
                        break;
                    }
                }
                //                if (works == true)
                //                {
                //                    state.mTest = true;
                //                }
                //                else if (works == false)
                //                {
                //                    state.mTest = false;
                //                }
            }
            break;
        default:
        case (MachineState::LEFT) :
            if (state.mXCor == 0) // || state.mTest == false)
            {
                break;
            }
            else
            {
                for (it = World::get().mZombieStates.begin(), itt = World::get().mZombieMachines.begin(); it != World::get().mZombieStates.end(); it++, itt++)
                {
                    if (state.mXCor-2 == (*it)->mXCor && state.mYCor == (*it)->mYCor)
                    {
                        works = false;
                        zombie = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mZombieStates.erase(it);
                            World::get().mZombieMachines.erase(itt);
                        }
                        break;
                    }
                }
                for (it2 = World::get().mHumanStates.begin(), itt2 = World::get().mHumanMachines.begin(); it2 != World::get().mHumanStates.end(); it2++, itt2++)
                {
                    if (state.mXCor-2 == (*it2)->mXCor && state.mYCor == (*it2)->mYCor)
                    {
                        works = false;
                        human = true;
                        if (state.GetActionsPerTurn() == 1)
                        {
                            // it's a zombie
                            
                        }
                        else if (state.GetActionsPerTurn() == 2)
                        {
                            // it's a human
                            World::get().mHumanStates.erase(it2);
                            World::get().mHumanMachines.erase(itt2);
                        }
                        
                        break;
                    }
                }
                
            }
            break;
    }

    state.mActionsTaken++;
    
}
