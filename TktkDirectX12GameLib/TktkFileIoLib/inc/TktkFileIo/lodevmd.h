#ifndef LODE_VMD_H_
#define LODE_VMD_H_

#include <string>
#include <vector>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Quaternion.h>

namespace tktkFileIo
{
	class lodevmd
	{
	public:

		struct loadData
		{
			struct OutMotionData
			{
				std::string				boneName;
				size_t					frameNo;
				tktkMath::Vector3		location;
				tktkMath::Quaternion	rotation;
				unsigned char			bezier[64];
			};

			std::vector<OutMotionData> motionData;
		};

	public:

		static void load(loadData* out, const std::string& fileName);
	};
}
#endif // !LODE_VMD_H_