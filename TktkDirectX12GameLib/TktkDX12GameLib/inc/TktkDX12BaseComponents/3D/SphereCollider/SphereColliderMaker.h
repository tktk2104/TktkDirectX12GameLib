#ifndef SPHERE_COLLIDER_MAKER_H_
#define SPHERE_COLLIDER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "SphereCollider.h"

namespace tktk
{
	// SphereColliderのインスタンスを作成するクラス
	class SphereColliderMaker
	{
	private: /* プライベートコンストラクタ達 */

		SphereColliderMaker() = default;
		SphereColliderMaker(const SphereColliderMaker& other) = default;
		SphereColliderMaker& operator = (const SphereColliderMaker& other) = default;

	public:

		// インスタンス作成開始
		static SphereColliderMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<SphereCollider> create();

		// 当たり判定のグループを設定
		template <class CollisionGroupType, is_idType<CollisionGroupType> = nullptr>
		SphereColliderMaker& collisionGroupType(CollisionGroupType value) { return collisionGroupTypeImpl(static_cast<int>(value)); }

		// 当たり判定の半径を設定
		SphereColliderMaker& radius(float value);

		// 当たり判定のローカル座標を設定
		SphereColliderMaker& localPosition(const tktkMath::Vector3& value);

		// 押し出されやすさを設定（割合）
		SphereColliderMaker& extrudedRate(float value);

	private: /* 裏実装 */

		SphereColliderMaker& collisionGroupTypeImpl(int value);

	private:

		// 自身のポインタ
		static SphereColliderMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr		m_user{ };
		int					m_collisionGroupType{ 0 };
		float				m_radius{ 1.0f };
		tktkMath::Vector3	m_localPosition{ tktkMath::Vector3_v::zero };
		float				m_extrudedRate{ 0.0f };
	};
}
#endif // !SPHERE_COLLIDER_MAKER_H_