#include "Action.h"

/// <summary>
/// 
/// </summary>
/// <param name="newName"></param>
/// <param name="p"></param>
Action::Action(const std::string newName,  int p) : 
	m_name(newName), successRate(p)
{}

WalkLeftAction::WalkLeftAction(std::string newName, int p) :
	Action(newName, p)
{
}

WalkRightAction::WalkRightAction(std::string newName, int p) :
	Action(newName, p)
{

}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool WalkLeftAction::run()
{
	if (std::rand() % 100 < successRate)
	{
		std::cout << "Walking left" << std::endl;
		return true;
	}
	return false;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool WalkRightAction::run()
{
	if (std::rand() % 100 < successRate)
	{
		std::cout << "Walking right" << std::endl;
		return true;
	}
	return false;
}