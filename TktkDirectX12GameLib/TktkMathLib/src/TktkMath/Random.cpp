#include "TktkMath/Random.h"

namespace tktkMath
{
	std::mt19937 Random::m_mt;
	unsigned int Random::m_seed{ std::mt19937::default_seed };

	void Random::randomize()
	{
		std::random_device rd;
		randomize(rd());
	}

	void Random::randomize(unsigned int seed)
	{
		m_seed = seed;

		m_mt.seed(seed);
	}

	int Random::getRandI(int min, int max)
	{
		std::uniform_int_distribution<int> dist(min, max);
		return dist(m_mt);
	}

	float Random::getRandF(float min, float max)
	{
		std::uniform_real_distribution<float> dist(min, max);
		return dist(m_mt);
	}

	unsigned int Random::getSeed()
	{
		return m_seed;
	}
}