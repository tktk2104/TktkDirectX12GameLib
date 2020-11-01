#include "TktkDX12BaseComponents/3D/SphereCollider/SphereColliderMaker.h"

namespace tktk
{
	SphereColliderMaker SphereColliderMaker::m_self;

	SphereColliderMaker& SphereColliderMaker::makeStart(GameObjectPtr user)
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
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<SphereCollider>(
				m_collisionGroupType,
				m_radius,
				m_localPosition,
				m_isExtrude,
				m_extrudedRate
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<SphereCollider>(
			m_collisionGroupType,
			m_radius,
			m_localPosition,
			m_isExtrude,
			m_extrudedRate
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	SphereColliderMaker& SphereColliderMaker::radius(float value)
	{
		// 値を設定して自身の参照を返す
		m_radius = value;
		return *this;
	}

	SphereColliderMaker& SphereColliderMaker::localPosition(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_localPosition = value;
		return *this;
	}

	SphereColliderMaker& SphereColliderMaker::isExtrude(bool value)
	{
		// 値を設定して自身の参照を返す
		m_isExtrude = value;
		return *this;
	}

	SphereColliderMaker& SphereColliderMaker::extrudedRate(float value)
	{
		// 値を設定して自身の参照を返す
		m_extrudedRate = value;
		return *this;
	}

	SphereColliderMaker& SphereColliderMaker::collisionGroupTypeImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_collisionGroupType = value;
		return *this;
	}
}