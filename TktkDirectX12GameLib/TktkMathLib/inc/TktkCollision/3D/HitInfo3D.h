#ifndef HIT_INFO_3D_H_
#define HIT_INFO_3D_H_

#include <TktkMath/Structs/Vector3.h>

namespace tktkCollision
{
	// ３次元の衝突判定結果
	struct HitInfo3D
	{
		// 衝突したか？
		bool				isHit			{ false };

		// 衝突時自身を押し出す時のベクトル
		// ※相手を押し出す時のベクトルはこのベクトルを反転する
		tktkMath::Vector3	selfExtrudeVec	{ tktkMath::Vector3_v::zero };
	};
}
#endif // !HIT_INFO_3D_H_