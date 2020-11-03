#include "TktkDX12BaseComponents/2D/RectCollider/RectColliderMaker.h"

namespace tktk
{
	RectColliderMaker RectColliderMaker::m_self;

	RectColliderMaker & RectColliderMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = RectColliderMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	RectColliderMaker& RectColliderMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = RectColliderMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 引数の追加階層を設定
		m_self.m_targetState = targetState;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<RectCollider> RectColliderMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.hierarchy.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<RectCollider>(
				m_collisionGroupType,
				m_rectSize,
				m_localPosition,
				m_isExtrude,
				m_extrudedRate
				);
		}
		
		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<RectCollider>(
			m_collisionGroupType,
			m_rectSize,
			m_localPosition,
			m_isExtrude,
			m_extrudedRate
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	RectColliderMaker & RectColliderMaker::rectSize(const tktkMath::Vector2 & value)
	{
		// 値を設定して自身の参照を返す
		m_rectSize = value;
		return *this;
	}

	RectColliderMaker & RectColliderMaker::localPosition(const tktkMath::Vector2 & value)
	{
		// 値を設定して自身の参照を返す
		m_localPosition = value;
		return *this;
	}

	RectColliderMaker& RectColliderMaker::isExtrude(bool value)
	{
		// 値を設定して自身の参照を返す
		m_isExtrude = value;
		return *this;
	}

	RectColliderMaker& RectColliderMaker::extrudedRate(float value)
	{
		// 値を設定して自身の参照を返す
		m_extrudedRate = value;
		return *this;
	}

	RectColliderMaker& RectColliderMaker::collisionGroupTypeImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_collisionGroupType = value;
		return *this;
	}
}