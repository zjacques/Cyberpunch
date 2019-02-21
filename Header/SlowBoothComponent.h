#pragma once
#pragma once
#include "DJboothComponent.h"

class SlowBoothComponent : public DJBoothComponent
{
public:
	void run()
	{
		std::cout << "Slowing down booth\n";
	}


};