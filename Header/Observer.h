#pragma once
#include "Entity.h"
#include <algorithm>
#include <iostream>

enum Event
{
	DAMAGE_TAKEN,
	DAMAGE_DEALT,
	PHASE_DOWN,
	MATCH_ENDED,
	SUPER_STUN,
	PLAYER_KILLED
};

class Observer
{
public:
	virtual ~Observer(){}
	virtual void onNotify(Entity* entity, Event event) = 0;
};

class Subject
{
public:
	void notify(Entity* entity, Event event)
	{
		for (auto& observer : m_observers)
		{
			observer->onNotify(entity, event);
		}
	}

	void addObserver(Observer* observer)
	{
		//Add the observer to the vector
		m_observers.emplace_back(observer);
	}

	void removeObserver(Observer* observer)
	{
		//Remove observer from the vector
		m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
	}

private:
	std::vector<Observer*> m_observers; //vector of observers
};

class AchievementsListener : public Observer
{
public:
	void onNotify(Entity* entiti, Event event)
	{
		//Switch case on the event
		switch (event)
		{
		case DAMAGE_TAKEN:
			std::cout << "handling damage taken achievement event\n";
			break;
		case DAMAGE_DEALT:
			std::cout << "handling damage dealt achievement event\n";
			break;
		}
	}
};