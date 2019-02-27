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

namespace achievements
{
	struct Listener
	{
		static std::vector<Observer*> obs;
	};
}

class Subject
{
public:

	void notify(Entity* entity, Event event)
	{
		for (auto& observer : achievements::Listener::obs)
		{
			observer->onNotify(entity, event);
		}
	}

	void addObserver(Observer* observer)
	{
		//Add the observer to the vector
		achievements::Listener::obs.emplace_back(observer);
	}

	void removeObserver(Observer* observer)
	{
		//Remove observer from the vector
		achievements::Listener::obs.erase(std::remove(achievements::Listener::obs.begin(), achievements::Listener::obs.end(), observer), achievements::Listener::obs.end());
	}

	//std::vector<Observer*> m_observers;
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