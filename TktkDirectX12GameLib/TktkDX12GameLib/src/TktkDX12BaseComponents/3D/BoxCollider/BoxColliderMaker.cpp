#include "TktkDX12BaseComponents/3D/BoxCollider/BoxColliderMaker.h"

namespace tktk
{
	BoxColliderMaker BoxColliderMaker::m_self;

	BoxColliderMaker& BoxColliderMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BoxColliderMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	BoxColliderMaker& BoxColliderMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BoxColliderMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 引数の追加階層を設定
		m_self.m_targetState = targetState;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<BoxCollider> BoxColliderMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.hierarchy.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<BoxCollider>(
				m_collisionGroupType,
				m_boxSize,
				m_localPosition,
				m_isExtrude,
				m_extrudedRate
				);
		}
		
		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<BoxCollider>(
			m_collisionGroupType,
			m_boxSize,
			m_localPosition,
			m_isExtrude,
			m_extrudedRate
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	BoxColliderMaker& BoxColliderMaker::collisionGroupType(CollisionGroupTypeCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_collisionGroupType = value;
		return *this;
	}

	BoxColliderMaker& BoxColliderMaker::boxSize(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_boxSize = value;
		return *this;
	}

	BoxColliderMaker& BoxColliderMaker::localPosition(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_localPosition = value;
		return *this;
	}

	BoxColliderMaker& BoxColliderMaker::isExtrude(bool value)
	{
		// 値を設定して自身の参照を返す
		m_isExtrude = value;
		return *this;
	}

	BoxColliderMaker& BoxColliderMaker::extrudedRate(float value)
	{
		// 値を設定して自身の参照を返す
		m_extrudedRate = value;
		return *this;
	}
}