#pragma once
#include "DJboothComponent.h"
#include "Entity.h"
#include "PlayerPhysicsComponent.h"

class GravityBoothComponent : public DJBoothComponent
{
public: 
	void run()
	{
		std::cout << "Flipping Grvaity booth\n";


	}

};