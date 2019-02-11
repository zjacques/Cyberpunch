#ifndef ACTION_H
#define ACTION_H

#include "BehaviourTree.h"

class Action : public BehaviourTree::Node
{
private:
	std::string m_name;
	int successRate;
public:
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