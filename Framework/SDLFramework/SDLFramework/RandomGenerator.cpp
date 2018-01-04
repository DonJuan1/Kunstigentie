#include "RandomGenerator.h"

int RandomGenerator::generateInt(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

float RandomGenerator::generateFloat(float min, float max)
{
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(generator);
}
