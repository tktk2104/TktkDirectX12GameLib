#include "TktkDX12BaseComponents/2D/CircleCollider/CircleColliderMaker.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	CircleColliderMaker CircleColliderMaker::m_self;

	CircleColliderMaker & CircleColliderMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = CircleColliderMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<CircleCollider> CircleColliderMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<CircleCollider>(
			m_collisionGroupType,
			m_radius,
			m_localPosition,
			m_isExtrude,
			m_extrudedRate
			);
	}

	CircleColliderMaker& CircleColliderMaker::collisionGroupType(CollisionGroupTypeCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_collisionGroupType = value;
		return *this;
	}

	CircleColliderMaker & CircleColliderMaker::radius(float value)
	{
		// 値を設定して自身の参照を返す
		m_radius = value;
		return *this;
	}

	CircleColliderMaker & CircleColliderMaker::localPosition(const tktkMath::Vector2 & value)
	{
		// 値を設定して自身の参照を返す
		m_localPosition = value;
		return *this;
	}

	CircleColliderMaker& CircleColliderMaker::isExtrude(bool value)
	{
		// 値を設定して自身の参照を返す
		m_isExtrude = value;
		return *this;
	}

	CircleColliderMaker& CircleColliderMaker::extrudedRate(float value)
	{
		// 値を設定して自身の参照を返す
		m_extrudedRate = value;
		return *this;
	}
}