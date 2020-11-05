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
			CollisionGroupTypeCarrier collisionGroupType,	// 当たり判定のグループ番号
			const tktkMath::Vector3& boxSize,				// 当たり判定の大きさ
			const tktkMath::Vector3& localPosition,			// 当たり判定のローカル座標
			bool isExtrude,									// 衝突相手を押し出す処理を行うか？
			float extrudedRate								// 押し出されやすさ（割合）
		);

	public:

		// <PolymorphismFunc>
		void start();
		bool isCollide(const ComponentBasePtr& other);
		void afterCollide();

	public:

		// 当たり判定のクラスを取得
		const tktkCollision::BoundingMesh& getBoundingMesh() const;

		// 衝突相手を押し出す処理を行うか？
		bool isExtrud() const;

		// 押し出されやすさを取得
		float getExtrudedRate() const;

		// 座標管理コンポーネントを取得
		const ComponentPtr<Transform3D>& getTransform() const;

		// TODO : ３次元線分描画コンポーネントを作ってこの関数を不要にする
		const std::vector<tktkMath::Vector3>& getTempVerts() const;

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

		// TODO : ３次元線分描画コンポーネントを作ってこの変数を不要にする
		std::vector<tktkMath::Vector3> m_tempVerts;

		// AABBの衝突判定クラス
		tktkCollision::BoundingMesh	m_boundingMesh;

		// 衝突相手を押し出す処理を行うか？
		bool						m_isExtrude;

		// 押し出されやすさ（割合）
		float						m_extrudedRate;

		// 衝突相手と衝突結果を保持するリスト
		std::forward_list<HitInfo>	m_hitInfo3dPairList;

		// 自身の３次元座標コンポーネント
		ComponentPtr<Transform3D>	m_transform3D;
	};
}
#endif // !BOX_COLLIDER_H_