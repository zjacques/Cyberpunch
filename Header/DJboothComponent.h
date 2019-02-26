#pragma once
#include "Component.h"
#include "iostream"

class DJBoothComponent : public Component
{
public: 
	DJBoothComponent(Entity* pickUp) : bgSwitch(false), m_pickUp(pickUp){}
	virtual void run() = 0;
	virtual void update(double dt) = 0;
	bool bgSwitch;
	Entity* m_pickUp;
private:
};