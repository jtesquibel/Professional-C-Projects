#pragma once

#include <list>
#include <vector>
#include <string>
#include <map>
#include <iostream>

struct CodeContext
{
	std::vector<std::string> mOps;
    std::map<int, int> mGoTos;
};

class Node
{
public:
	virtual void CodeGen(CodeContext& context) const = 0;
};

class NNumeric : public Node
{
public:
	NNumeric(std::string& value);
	int mvalue;
	virtual void CodeGen(CodeContext& context) const override { }
};

class NStatement : public Node
{

};

class NRotate : public NStatement
{
public:
	NRotate(NNumeric* dir);
	virtual void CodeGen(CodeContext& context) const override;
private:
	NNumeric* mDir;
};

class NBoolean : public Node
{
};

class NBlock : public Node
{
public:
	NBlock() { mbMainBlock = false; }
	virtual void CodeGen(CodeContext& context) const override;
	void AddStatement(NStatement* statement);
	void SetMainBlock() { mbMainBlock = true; }
private:
	std::list<NStatement*> mStatements;
	bool mbMainBlock;
};

class NForward : public NStatement
{
public:
    NForward();
    virtual void CodeGen(CodeContext& context) const override;
private:
   
};

class NAttack : public NStatement
{
public:
    NAttack();
    virtual void CodeGen(CodeContext& context) const override;
private:
};

class NRangedAttack : public NStatement
{
public:
    NRangedAttack();
    virtual void CodeGen(CodeContext& context) const override;
private:
};

class NIsHuman : public NBoolean
{
public:
    NIsHuman(NNumeric* dir);
    virtual void CodeGen(CodeContext& context) const override;
private:
    NNumeric* mDir;
};

class NIsZombie : public NBoolean
{
public:
    NIsZombie(NNumeric* dir);
    virtual void CodeGen(CodeContext& context) const override;
private:
    NNumeric* mDir;
};

class NIsPassable : public NBoolean
{
public:
    NIsPassable();
    virtual void CodeGen(CodeContext& context) const override;
private:
};

class NIsRandom : public NBoolean
{
public:
    NIsRandom();
    virtual void CodeGen(CodeContext& context) const override;
private:
};

class NIf : public NStatement
{
public:
    NIf(NBoolean* boolCom);
    virtual void CodeGen(CodeContext& context) const override;
private:
    NBoolean* mBool;
};

class NElse : public NStatement
{
public:
    NElse();
    virtual void CodeGen(CodeContext& context) const override;
private:
};

class NIfElse : public NStatement
{
public:
    NIfElse(NStatement* ifStat, NBlock* ifBlock, NBlock* elseBlock);
    virtual void CodeGen(CodeContext& context) const override;
private:
    NStatement* mIfStat;
    NBlock* mIfBlock;
    NBlock* mElseBlock;
};
