#ifndef MOTION_BONE_PARAM_H_
#define MOTION_BONE_PARAM_H_

/* class member */
#include <string>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// ボーン毎の座標変換情報
	struct MotionBoneParam
	{
		// ボーンの名前
		std::string			boneName;

		// 座標変換行列
		tktkMath::Matrix4	transform;
	};
}
#endif // !MOTION_BONE_PARAM_H_
