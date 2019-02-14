#ifndef ACTION_H
#define ACTION_H

#include "BehaviourTree.h"


class Action : public BehaviourTree::Node
{
private:

public:
	//MovementSystem * m_moveSystem;
	std::string m_name;
	int successRate;
	Action(const std::string newName, int p) : m_name(newName), successRate(p) {}
	//void addMovementSystem(MovementSystem * m) { m_moveSystem = m; }
private:
	virtual bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Success" << std::endl;
			return true;
		}
		return false;
	}
};

#endif

#ifndef WALKLEFTACTION_H
#define WALKLEFTACTION_H

class WalkLeftAction : public Action
{
	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Walking left" << std::endl;
			//Move the player left
			//m_moveSystem->Left();
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
	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Walking right" << std::endl;
			//m_moveSystem->Right();
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
	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Jump" << std::endl;
			//m_moveSystem->Jump();
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
