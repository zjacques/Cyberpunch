#pragma once
#pragma once
#include "DJboothComponent.h"

class PlatformBoothComponent : public DJBoothComponent
{
public:
	void run()
	{
		std::cout << "Platform moving booth\n";
	}


};