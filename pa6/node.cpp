#include "node.h"
#include <sstream>

void NBlock::AddStatement(NStatement* statement)
{
	mStatements.push_back(statement);
}

void NBlock::CodeGen(CodeContext& context) const
{
	// TODO: Loop through statements in list and code gen them
    for (auto it = mStatements.begin(); it != mStatements.end(); it++)
    {
        (*it)->CodeGen(context);
    }
    
    // check if current block is main block
    if (this->mbMainBlock == true)
    {
        context.mOps.push_back("goto,1");
        context.mGoTos.insert(std::make_pair(context.mOps.size(), 1));
    }

}

NNumeric::NNumeric(std::string& value)
{
	mvalue = std::atoi(value.c_str());
}

NRotate::NRotate(NNumeric* dir)
	: mDir(dir)
{
}

void NRotate::CodeGen(CodeContext& context) const
{
	if (mDir->mvalue == 0)
	{
		context.mOps.push_back("rotate,0");
	}
	else if (mDir->mvalue == 1)
	{
		context.mOps.push_back("rotate,1");
	}
}

NForward::NForward()
{
}

void NForward::CodeGen(CodeContext& context) const
{
    context.mOps.push_back("forward");
}

NAttack::NAttack()
{
    
}

void NAttack::CodeGen(CodeContext& context) const
{
    context.mOps.push_back("attack");
}

NRangedAttack::NRangedAttack()
{
}

void NRangedAttack::CodeGen(CodeContext& context) const
{
    context.mOps.push_back("ranged_attack");
}

NIsHuman::NIsHuman(NNumeric* dir)
    : mDir(dir)
{
}

void NIsHuman::CodeGen(CodeContext& context) const
{
    if (mDir->mvalue == 1)
    {
        context.mOps.push_back("test_human,1");
    }
    else if (mDir->mvalue == 2)
    {
        context.mOps.push_back("test_human,2");
    }
}

NIsZombie::NIsZombie(NNumeric* dir)
    : mDir(dir)
{
}

void NIsZombie::CodeGen(CodeContext& context) const
{
    if (mDir->mvalue == 1)
    {
        context.mOps.push_back("test_zombie,1");
    }
    else if (mDir->mvalue == 2)
    {
        context.mOps.push_back("test_zombie,2");
    }
}

NIsPassable::NIsPassable()
{
}

void NIsPassable::CodeGen(CodeContext& context) const
{
    context.mOps.push_back("test_passable");
}

NIsRandom::NIsRandom()
{
}

void NIsRandom::CodeGen(CodeContext& context) const
{
    context.mOps.push_back("test_random");
}

NIf::NIf(NBoolean* boolCom)
    : mBool(boolCom)
{
}

void NIf::CodeGen(CodeContext& context) const
{
    mBool->CodeGen(context);
}

NElse::NElse()
{
}

void NElse::CodeGen(CodeContext& context) const
{
}

NIfElse::NIfElse(NStatement* ifStat, NBlock* ifBlock, NBlock* elseBlock)
    : mIfStat(ifStat),
    mIfBlock(ifBlock),
    mElseBlock(elseBlock)
{
    
}

void NIfElse::CodeGen(CodeContext& context) const
{
    mIfStat->CodeGen(context);
    
    int je = static_cast<int>(context.mOps.size());
    context.mOps.push_back("je,?");
    mElseBlock->CodeGen(context);
    
    int goTo = static_cast<int>(context.mOps.size());
    context.mOps.push_back("goto,?");
    mIfBlock->CodeGen(context);

    // go back and change the values they point to
    context.mOps[je] = "je," + std::to_string(context.mOps.size());
    context.mOps[goTo] = "goto," + std::to_string(context.mOps.size()+1);
    context.mGoTos.insert(std::make_pair(goTo+1, context.mOps.size()+1));
    
    
}

