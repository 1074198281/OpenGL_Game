#include "stdio.h"
#include "math.h"


float clamp(float value, float min, float max)
{
	return min > (max > value ? max : value) ? min : (max > value ? max : value);
}

