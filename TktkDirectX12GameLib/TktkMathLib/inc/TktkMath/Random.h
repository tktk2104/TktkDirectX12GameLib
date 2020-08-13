#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>

namespace tktkMath
{
	// 乱数生成クラス
	class Random
	{
	public:

		// 乱数の初期化
		static void randomize();

		// 乱数のシード値を自前で指定して乱数を初期化
		static void randomize(unsigned int seed);

		static int getRandI(int min, int max);

		static float getRandF(float min, float max);

		static unsigned int getSeed();

	private:

		static std::mt19937 m_mt;

		static unsigned int m_seed;
	};
}
#endif // !RANDOM_H_