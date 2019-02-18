#ifndef ACTION_H
#define ACTION_H

#include "BehaviourTree.h"

class Action : public BehaviourTree::Node
{
private:

public:
	std::string m_name;
	int successRate;
	Action(const std::string newName, int p) : m_name(newName), successRate(p) {}

	virtual bool run() = 0;
};

#endif

#ifndef WALKLEFTACTION_H
#define WALKLEFTACTION_H

class WalkLeftAction : public Action
{
public:
	WalkLeftAction(std::string newName, int p)
		: Action(newName, p)
	{
	}

	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Walking left" << std::endl;
			return true;
		}
		return false;
	}
};

#endif

#ifndef WALKRIGHTACTION_H
#define WALKRIGHTACTION_H

class WalkRightAction : public Action
{
public:
	WalkRightAction(std::string newName, int p)
		: Action(newName, p)
	{
	}
	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Walking right" << std::endl;
			return true;
		}
		return false;
	}
};

#endif

#ifndef JUMPACTION_H
#define JUMPACTION_H

class JumpAction : public Action
{
public:
	JumpAction(std::string newName, int p)
		: Action(newName, p)
	{
	}
	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Jump" << std::endl;
			return true;
		}
		return false;
	}
};

#endif

#ifndef PUNCHACTION_H
#define PUNCHACTION_H

class PunchAction : public Action
{
public:
	PunchAction(std::string newName, int p)
		: Action(newName, p)
	{
	}
	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Punch" << std::endl;
			return true;
		}
		return false;
	}
};

#endif

#ifndef CHECKNEAREST_H
#define CHECKNEAREST_H

class CheckNearest : public Action
{
public:
	CheckNearest(std::string newName, int p) :
		Action(newName, p)
	{
	}

	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			//std::cout << "Getting nearest player" << std::endl;
			return true;
		}
		return false;
	}
};

#endif

#ifndef CLOSEENOUGH_H
#define CLOSEENOUGH_H

class CloseEnough : public Action
{
public:
	CloseEnough(std::string newName, int p) :
		Action(newName, p)
	{
	}

	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Close enough" << std::endl;
			return true;
		}
		return false;
	}
};

#endif

#ifndef CHECKPLAYERDIRECTION_H
#define CHECKPLAYERDIRECTION_H

class CheckPlayerDirection : public Action
{
public:
	CheckPlayerDirection(std::string newName, int p) :
		Action(newName, p)
	{
	}

	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Check direction" << std::endl;
			return true;
		}
		return false;
	}
};

#endif

