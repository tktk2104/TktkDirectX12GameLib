#ifndef SPHERE_COLLIDER_H_
#define SPHERE_COLLIDER_H_

#include <TktkMath/Structs/Vector3.h>
#include <TktkCollision/3D/BoundingSphere.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// 球体の当たり判定のコンポーネント
	// 【前提コンポーネント：Transform3D】
	class SphereCollider
		: public ComponentBase
	{
	public:

		SphereCollider(
			int collisionGroupType,			// 当たり判定のグループ番号
			float radius,					// 当たり判定の半径
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

		// 球体の衝突判定クラス
		BoundingSphere m_boundingSphere;

		// 自身の３次元座標コンポーネント
		ComponentPtr<Transform3D> m_transform3D;
	};
}
#endif // !SPHERE_COLLIDER_H_