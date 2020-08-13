#ifndef LODE_BMP_H_
#define LODE_BMP_H_

#include <string>
#include <vector>

namespace tktk
{
	// ※「OS/2」フォーマットには未対応
	class lodebmp
	{
	public:

		struct loadData
		{
			unsigned int width;
			unsigned int height;
			std::vector<unsigned char> data;
		};

	public:

		static void load(loadData* out, const std::string& fileName);
	};
}
#endif // !LODE_BMP_H_