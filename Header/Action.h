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
private:
	virtual bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << m_name << " succeeded" << std::endl;
			return true;
		}
		std::cout << m_name << " failed" << std::endl;
		return false;
	}
};

#endif

#ifndef WALKLEFTACTION_H
#define WALKLEFTACTION_H

class WalkLeftAction : public Action
{
	bool run()
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Walking left" << std::endl;
			//Move the player left
		}
	}
};

#endif


#ifndef WALKRIGHTACTION_H
#define WALKRIGHTACTION_H

class WalkRightAction : public Action
{
	bool run()
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Walking right" << std::endl;
		}
	}
};

#endif
