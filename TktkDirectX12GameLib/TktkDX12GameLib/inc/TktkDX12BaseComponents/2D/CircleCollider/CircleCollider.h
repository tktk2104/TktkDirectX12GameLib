#ifndef CIRCLE_COLLIDER_H_
#define CIRCLE_COLLIDER_H_

#include <forward_list>
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
			const tktkMath::Vector2& localPosition,	// 当たり判定のローカル座標
			float extrudedRate						// 押し出されやすさ（割合）
		);

	public:

		// <PolymorphismFunc>
		void start();
		bool isCollide(const ComponentBasePtr& other);
		void afterCollide();

	public:

		// 当たり判定のクラスを取得
		const tktkCollision::BoundingCircle& getBoundingCircle() const;

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

			float						otherExtrudedRate;

			tktkCollision::HitInfo2D	hitInfo;
		};
	private:

		// 円の衝突判定クラス
		tktkCollision::BoundingCircle	m_boundingCircle;

		// 押し出されやすさ（割合）
		float							m_extrudedRate;

		// 衝突相手と衝突結果を保持するリスト
		std::forward_list<HitInfo>		m_hitInfo2dPairList;

		// 自身の２次元座標コンポーネント
		ComponentPtr<Transform2D>		m_transform2D;
	};
}
#endif // !CIRCLE_COLLIDER_H_