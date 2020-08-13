#ifndef SKELETON_INIT_PARAM_H_
#define SKELETON_INIT_PARAM_H_

#include <string>
#include <vector>
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	// スケルトンを作るときに必要な情報
	struct SkeletonInitParam
	{
		// ボーン毎の情報
		struct BoneData
		{
			// ボーンの名前
			std::string			boneName;

			// 親のID
			unsigned short		parentNo;

			// ボーンの位置
			tktkMath::Vector3	pos;
		};

		// ボーン情報の配列
		std::vector<BoneData> boneDataArray;
	};
}
#endif // !SKELETON_INIT_PARAM_H_
