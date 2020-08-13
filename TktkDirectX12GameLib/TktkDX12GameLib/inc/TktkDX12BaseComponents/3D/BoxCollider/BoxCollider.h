#ifndef BOX_COLLIDER_H_
#define BOX_COLLIDER_H_

#include <TktkCollision/3D/AxisAlignedBoundingBox.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// AABBの当たり判定のコンポーネント
	// 【前提コンポーネント：Transform3D】
	class BoxCollider
		: public ComponentBase
	{
	public:

		BoxCollider(
			int collisionGroupType,					// 当たり判定のグループ番号
			const tktkMath::Vector3& boxSize,		// 当たり判定の大きさ
			const tktkMath::Vector3& localPosition	// 当たり判定のローカル座標
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();
		bool isCollide(const ComponentBasePtr& other);

	public:

		// 当たり判定のクラスを取得
		const Body3dBase& getBodyBase() const;

		// 直前の衝突判定の結果を取得
		const HitInfo3D& getHitInfo3D() const;

	private:

		// 衝突判定結果
		HitInfo3D m_hitInfo;

		// AABBの衝突判定クラス
		AxisAlignedBoundingBox m_boundingBox;

		// 自身の３次元座標コンポーネント
		ComponentPtr<Transform3D> m_transform3D;
	};
}
#endif // !BOX_COLLIDER_H_