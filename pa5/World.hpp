//
//  World.hpp
//  zombiewx-mac
//
//  Created by Jonathan Esquibel on 3/22/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include "Singleton.h"
#include "Machine.h"
#include "Traits.h"

#define DECLARE_SINGLETON(SingletonClass) friend class Singleton<SingletonClass>;

class World : public Singleton<World>
{
    DECLARE_SINGLETON(World)
public:

    std::vector<std::shared_ptr<MachineState>> mZombieStates;
    std::vector<std::shared_ptr<Machine<ZombieTraits>>> mZombieMachines;
    std::vector<std::shared_ptr<MachineState>> mHumanStates;
    std::vector<std::shared_ptr<Machine<HumanTraits>>> mHumanMachines;
    
    std::string mZombieFileName;
    std::string mHumanFileName;
    
    int mTurns;
    
private:
    World();
};

#endif /* World_hpp */
