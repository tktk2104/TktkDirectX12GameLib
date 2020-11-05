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

		// ステートを指定し、作成を開始する
		static SphereColliderMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<SphereCollider> create();

		// 当たり判定のグループを設定
		SphereColliderMaker& collisionGroupType(CollisionGroupTypeCarrier value);

		// 当たり判定の半径を設定
		SphereColliderMaker& radius(float value);

		// 当たり判定のローカル座標を設定
		SphereColliderMaker& localPosition(const tktkMath::Vector3& value);

		// 衝突相手を押し出す処理を行うか？
		SphereColliderMaker& isExtrude(bool value);

		// 押し出されやすさを設定（割合）
		SphereColliderMaker& extrudedRate(float value);

	private:

		// 自身のポインタ
		static SphereColliderMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr				m_user				{ };
		StateTypeHierarchy			m_targetState		{  };
		CollisionGroupTypeCarrier	m_collisionGroupType{ 0 };
		float						m_radius			{ 1.0f };
		tktkMath::Vector3			m_localPosition		{ tktkMath::Vector3_v::zero };
		bool						m_isExtrude			{ false };
		float						m_extrudedRate		{ 0.0f };
	};
}
#endif // !SPHERE_COLLIDER_MAKER_H_