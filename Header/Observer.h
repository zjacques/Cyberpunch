#pragma once
#include "Entity.h"
#include <algorithm>
#include <iostream>
#include "Component.h"
#include "System.h"

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

namespace achi
{
	struct Listener
	{
		static std::vector<Observer*> obs;
		static Component* m_AchisPtr;
		static std::vector<std::string> m_newUnlocks;
	};
}

class Subject
{
public:

	void notify(Entity* entity, Event event)
	{
		for (auto& observer : achi::Listener::obs)
		{
			observer->onNotify(entity, event);
		}
	}

	void addObserver(Observer* observer)
	{
		//Add the observer to the vector
		achi::Listener::obs.emplace_back(observer);
	}

	void removeObserver(Observer* observer)
	{
		//Remove observer from the vector
		achi::Listener::obs.erase(std::remove(achi::Listener::obs.begin(), achi::Listener::obs.end(), observer), achi::Listener::obs.end());
	}
};

class AchievementsListener : public Observer
{
public:
	AchievementsListener(){}

	void onNotify(Entity* entiti, Event event);
private:
};