#ifndef CIRCLE_COLLIDER_H_
#define CIRCLE_COLLIDER_H_

/* std::forward_list */
#include <forward_list>

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>

/* class member */
#include <TktkCollision/2D/BoundingCircle.h>

/* baseClass */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	/* class member */
	class Transform2D;
	class InertialMovement2D;

	// 真円の当たり判定のコンポーネント
	// 【前提コンポーネント：Transform2D】
	class CircleCollider
		: public ComponentBase
	{
	public:

		CircleCollider(
			CollisionGroupTypeCarrier collisionGroupType,	// 当たり判定のグループ番号
			float radius,									// 当たり判定の半径
			const tktkMath::Vector2& localPosition,			// 当たり判定のローカル座標
			bool isExtrude,									// 衝突相手を押し出す処理を行うか？
			float extrudedRate								// 押し出されやすさ（割合）
		);

	public:

		// <PolymorphismFunc>
		void start();
		void beforeCollide();
		bool isCollide(const ComponentBasePtr& other);
		void afterCollide();

	public:

		// 当たり判定のクラスを取得
		const tktkCollision::BoundingCircle& getBoundingCircle() const;

		// 衝突相手を押し出す処理を行うか？
		bool isExtrud() const;

		// 押し出されやすさを取得
		float getExtrudedRate() const;

		// 座標管理コンポーネントを取得
		const ComponentPtr<Transform2D>& getTransform() const;

	private:

		// 自身の押し出し処理
		void extrusion();

	private:

		struct HitInfo
		{
			GameObjectPtr				otherObject;

			bool						isExtrude;

			float						otherExtrudedRate;

			tktkCollision::HitInfo2D	hitInfo;
		};
	private:

		// 円の衝突判定クラス
		tktkCollision::BoundingCircle		m_boundingCircle;

		// 衝突相手を押し出す処理を行うか？
		bool								m_isExtrude;

		// 押し出されやすさ（割合）
		float								m_extrudedRate;

		// 衝突相手と衝突結果を保持するリスト
		std::forward_list<HitInfo>			m_hitInfo2dPairList;

		// 自身の２次元座標コンポーネント
		ComponentPtr<Transform2D>			m_transform2D;

		// 自身の２次元慣性移動コンポーネント
		ComponentPtr<InertialMovement2D>	m_inertialMovement2D;
	};
}
#endif // !CIRCLE_COLLIDER_H_