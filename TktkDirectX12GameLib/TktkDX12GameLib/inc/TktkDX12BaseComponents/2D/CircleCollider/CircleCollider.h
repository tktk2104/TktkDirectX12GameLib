#ifndef CIRCLE_COLLIDER_H_
#define CIRCLE_COLLIDER_H_

#include <TktkMath/Structs/Vector2.h>
#include <TktkCollision/2D/BoundingCircle.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform2D/Transform2D.h"

namespace tktk
{
	// 真円の当たり判定のコンポーネント
	// 【前提コンポーネント：Transform2D】
	class CircleCollider
		: public ComponentBase
	{
	public:

		CircleCollider(
			int collisionGroupType,					// 当たり判定のグループ番号
			float radius,							// 当たり判定の半径
			const tktkMath::Vector2& localPosition	// 当たり判定のローカル座標
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();
		bool isCollide(const ComponentBasePtr& other);

	public:

		// 当たり判定のクラスを取得
		const tktkCollision::Body2dBase& getBodyBase() const;

		// 直前の衝突判定の結果を取得
		const tktkCollision::HitInfo2D& getHitInfo2D() const;

	private:

		// 衝突判定結果
		tktkCollision::HitInfo2D m_hitInfo;

		// 円の衝突判定クラス
		tktkCollision::BoundingCircle m_boundingCircle;

		// 自身の２次元座標コンポーネント
		ComponentPtr<Transform2D> m_transform2D;
	};
}
#endif // !CIRCLE_COLLIDER_H_