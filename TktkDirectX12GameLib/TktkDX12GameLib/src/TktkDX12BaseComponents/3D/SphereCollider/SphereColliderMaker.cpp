#include "TktkDX12BaseComponents/3D/SphereCollider/SphereColliderMaker.h"

namespace tktk
{
	SphereColliderMaker SphereColliderMaker::m_self;

	SphereColliderMaker & SphereColliderMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = SphereColliderMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<SphereCollider>SphereColliderMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<SphereCollider>(
			m_collisionGroupType,
			m_radius,
			m_localPosition
			);
	}

	SphereColliderMaker & SphereColliderMaker::radius(float value)
	{
		// 値を設定して自身の参照を返す
		m_radius = value;
		return *this;
	}

	SphereColliderMaker & SphereColliderMaker::localPosition(const tktkMath::Vector3 & value)
	{
		// 値を設定して自身の参照を返す
		m_localPosition = value;
		return *this;
	}

	SphereColliderMaker& SphereColliderMaker::collisionGroupTypeImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_collisionGroupType = value;
		return *this;
	}
}