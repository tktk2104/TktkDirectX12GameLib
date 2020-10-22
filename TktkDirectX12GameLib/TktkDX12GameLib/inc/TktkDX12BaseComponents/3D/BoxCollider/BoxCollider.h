#ifndef BOX_COLLIDER_H_
#define BOX_COLLIDER_H_

#include <TktkCollision/3D/BoundingMesh.h>
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
			const tktkMath::Vector3& localPosition,	// 当たり判定のローカル座標
			float extrudedRate						// 押し出されやすさ（割合）
		);

	public:

		// <PolymorphismFunc>
		void start();
		bool isCollide(const ComponentBasePtr& other);
		void afterCollide();

	public:

		// 当たり判定のクラスを取得
		const tktkCollision::BoundingMesh& getBoundingMesh() const;

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

			float						otherExtrudedRate;

			tktkCollision::HitInfo3D	hitInfo;
		};

	private:

		// AABBの衝突判定クラス
		tktkCollision::BoundingMesh	m_boundingMesh;

		// 押し出されやすさ（割合）
		float						m_extrudedRate;

		// 衝突相手と衝突結果を保持するリスト
		std::forward_list<HitInfo>	m_hitInfo3dPairList;

		// 自身の３次元座標コンポーネント
		ComponentPtr<Transform3D>	m_transform3D;
	};
}
#endif // !BOX_COLLIDER_H_