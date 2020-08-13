#include "TktkFileIo/lodevmd.h"

#include <filesystem>

namespace tktkFileIo
{
#pragma pack(push, 1)
	struct VmdMotion
	{
		char					boneName[15];
		unsigned int			frameNo;
		tktkMath::Vector3		location;
		tktkMath::Quaternion	rotation;
		unsigned char			bezier[64];
	};
#pragma pack(pop)

	void lodevmd::load(loadData* out, const std::string& fileName)
	{
		FILE* fp;
		fopen_s(&fp, fileName.c_str(), "rb");

		fseek(fp, 50, SEEK_SET);

		unsigned int motionDataNum;
		fread(&motionDataNum, sizeof(unsigned int), 1, fp);

		std::vector<VmdMotion> tempMotionData(motionDataNum);
		fread(tempMotionData.data(), tempMotionData.size() * sizeof(VmdMotion), 1, fp);

		out->motionData.clear();
		out->motionData.resize(motionDataNum);

		for (unsigned int i = 0; i < motionDataNum; i++)
		{
			out->motionData.at(i).boneName	= tempMotionData.at(i).boneName;
			out->motionData.at(i).frameNo	= tempMotionData.at(i).frameNo;
			out->motionData.at(i).location	= tempMotionData.at(i).location;
			out->motionData.at(i).rotation	= tempMotionData.at(i).rotation;

			for (unsigned int j = 0; j < 64; j++)
			{
				out->motionData.at(i).bezier[j] = tempMotionData.at(i).bezier[j];
			}
		}
	}
}