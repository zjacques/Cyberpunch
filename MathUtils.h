#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <random>

class MathUtils
{
public:
	static int random(int min, int max)
	{
		double x = rand() / static_cast<double>(RAND_MAX + 1);
		int val = min + static_cast<int>(x * (max - min));
		return val;
	}
};

#endif
