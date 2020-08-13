#ifndef HIT_INFO_2D_H_
#define HIT_INFO_2D_H_

#include <string>
#include "../../../TktkMath/Structs/Vector2.h"

// 衝突判定の結果
struct HitInfo2D
{
public:

	HitInfo2D()
		: isHit(false)
		, selfPointClosestToOther(tktkMath::vec2Zero)
		, otherPointClosestToSelf(tktkMath::vec2Zero)
	{}

public:

	// 衝突したか？
	bool isHit;

	// 自身の当たり判定の中心座標から見て 相手の当たり判定に一番近い座標
	tktkMath::Vector2 selfPointClosestToOther;

	// 相手の当たり判定の中心座標から見て 自身の当たり判定に一番近い座標
	tktkMath::Vector2 otherPointClosestToSelf;
};

#endif // !HIT_INFO_2D_H_