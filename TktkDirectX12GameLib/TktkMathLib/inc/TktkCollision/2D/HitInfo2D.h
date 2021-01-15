#ifndef HIT_INFO_2D_H_
#define HIT_INFO_2D_H_

#include <TktkMath/Structs/Vector2.h>

namespace tktkCollision
{
	// ２次元の衝突判定結果
	struct HitInfo2D
	{
		// 衝突したかどうか？
		bool				isHit			{ false };

		// 衝突時自身を押し出す時のベクトル
		// ※相手を押し出す時のベクトルはこのベクトルを反転する
		tktkMath::Vector2	selfExtrudeVec	{ tktkMath::Vector2_v::zero };
	};


}
#endif // !HIT_INFO_2D_H_