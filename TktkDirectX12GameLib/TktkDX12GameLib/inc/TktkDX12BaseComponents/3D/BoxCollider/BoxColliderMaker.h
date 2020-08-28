#ifndef BOX_COLLIDER_MAKER_H_
#define BOX_COLLIDER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BoxCollider.h"

namespace tktk
{
	// BoxColliderのインスタンスを作成するクラス
	class BoxColliderMaker
	{
	private: /* プライベートコンストラクタ達 */

		BoxColliderMaker() = default;
		BoxColliderMaker(const BoxColliderMaker& other) = default;
		BoxColliderMaker& operator = (const BoxColliderMaker& other) = default;

	public:

		// インスタンス作成開始
		static BoxColliderMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<BoxCollider> create();

		// 当たり判定のグループを設定
		template <class CollisionGroupType, is_idType<CollisionGroupType> = nullptr>
		BoxColliderMaker& collisionGroupType(CollisionGroupType value) { return collisionGroupTypeImpl(static_cast<int>(value)); }

		// 当たり判定の大きさを設定
		BoxColliderMaker& boxSize(const tktkMath::Vector3& value);

		// 当たり判定のローカル座標を設定
		BoxColliderMaker& localPosition(const tktkMath::Vector3& value);

	private: /* 裏実装 */

		BoxColliderMaker& collisionGroupTypeImpl(int value);

	private:

		// 自身のポインタ
		static BoxColliderMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr		m_user				{ };
		int					m_collisionGroupType{ 0 };
		tktkMath::Vector3	m_boxSize			{ tktkMath::Vector3_v::one };
		tktkMath::Vector3	m_localPosition		{ tktkMath::Vector3_v::zero };
	};
}
#endif // !BOX_COLLIDER_MAKER_H_