// Defines all the classes for different operations
// which can be performed.
#pragma once

struct MachineState;

// Abstract Base Class
class Op
{
public:
	Op(const char* OpName, int parameter)
		: mOpName(OpName)
		, mParam(parameter)
	{ }

	void DebugOutput(MachineState& state);

	virtual void Execute(MachineState& state) = 0;

	MachineState* GetTarget(MachineState& state, int n = 1);
	
	virtual ~Op() { }
protected:
	int mParam;
	const char* mOpName;
};

// Defines the rotate operation
// Param of 0 means rotate clockwise
// Param of 1 means rotate counter-clockwise
struct OpRotate : Op
{
	OpRotate(int parameter)
		: Op("OpRotate", parameter)
	{ }

	virtual void Execute(MachineState& state) override;
};

// Defines the goto operation
// Parameter determines the line number
struct OpGoTo : Op
{
	OpGoTo(int parameter)
		: Op("OpGoTo", parameter)
	{ }

	virtual void Execute(MachineState& state) override;
};

struct OpTestWall : Op
{
    OpTestWall(int parameter)
    : Op("OpTestWall", parameter)
    { }
    
    virtual void Execute(MachineState& state) override;
};

struct OpJE : Op
{
    OpJE(int parameter)
    : Op("OpJE", parameter)
    { }
    
    virtual void Execute(MachineState& state) override;
};

struct OpForward : Op
{
    OpForward(int parameter)
    : Op("OpForward", parameter)
    { }
    
    virtual void Execute(MachineState& state) override;
};

struct OpTestRandom : Op
{
    OpTestRandom(int parameter)
    : Op("OpTestRandom", parameter)
    { }
    
    virtual void Execute(MachineState& state) override;
};

struct OpEndTurn : Op
{
    OpEndTurn(int parameter)
    : Op("OpEndTurn", parameter)
    { }
    
    virtual void Execute(MachineState& state) override;
};

struct OpTestHuman : Op
{
    OpTestHuman(int parameter)
    : Op("OpTestHuman", parameter)
    { }
    
    virtual void Execute(MachineState& state) override;
};

struct OpTestZombie : Op
{
    OpTestZombie(int parameter)
    : Op("OpTestZombie", parameter)
    { }
    
    virtual void Execute(MachineState& state) override;
};

struct OpTestPassable : Op
{
    OpTestPassable(int parameter)
    : Op("OpTestPassable", parameter)
    { }
    
    virtual void Execute(MachineState& state) override;
};

struct OpJNE : Op
{
    OpJNE(int parameter)
    : Op("OpJNE", parameter)
    { }
    
    virtual void Execute(MachineState& state) override;
};

struct OpAttack : Op
{
    OpAttack(int parameter)
    : Op("OpAttack", parameter)
    { }
    
    virtual void Execute(MachineState& state) override;
};

struct OpRangedAttack : Op
{
    OpRangedAttack(int parameter)
    : Op("OpRangedAttack", parameter)
    { }
    
    virtual void Execute(MachineState& state) override;
};

