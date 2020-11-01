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
			int collisionGroupType,					// 当たり判定のグループ番号
			float radius,							// 当たり判定の半径
			const tktkMath::Vector3& localPosition,	// 当たり判定のローカル座標
			bool isExtrude,							// 衝突相手を押し出す処理を行うか？
			float extrudedRate						// 押し出されやすさ（割合）
		);

	public:

		// <PolymorphismFunc>
		void start();
		bool isCollide(const ComponentBasePtr& other);
		void afterCollide();

	public:

		// 当たり判定のクラスを取得
		const tktkCollision::BoundingSphere& getBoundingSphere() const;

		// 衝突相手を押し出す処理を行うか？
		bool isExtrud() const;

		// 押し出されやすさを取得
		float getExtrudedRate() const;

		// 座標管理コンポーネントを取得
		const ComponentPtr<Transform3D>& getTransform() const;

	private:

		// 自身の押し出し処理
		void extrusion();

	private:

		struct HitInfo
		{
			GameObjectPtr				otherObject;

			bool						isExtrude;

			float						otherExtrudedRate;

			tktkCollision::HitInfo3D	hitInfo;
		};

	private:

		// 球体の衝突判定クラス
		tktkCollision::BoundingSphere m_boundingSphere;

		// 衝突相手を押し出す処理を行うか？
		bool						m_isExtrude;

		// 押し出されやすさ（割合）
		float						m_extrudedRate;

		// 衝突相手と衝突結果を保持するリスト
		std::forward_list<HitInfo>	m_hitInfo3dPairList;

		// 自身の３次元座標コンポーネント
		ComponentPtr<Transform3D> m_transform3D;
	};
}
#endif // !SPHERE_COLLIDER_H_