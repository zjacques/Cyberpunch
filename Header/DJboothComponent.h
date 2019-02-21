#pragma once
#include "Component.h"
#include "iostream"

class DJBoothComponent : public Component
{
public: 
	DJBoothComponent() {}
	virtual void run() = 0;
private:
};