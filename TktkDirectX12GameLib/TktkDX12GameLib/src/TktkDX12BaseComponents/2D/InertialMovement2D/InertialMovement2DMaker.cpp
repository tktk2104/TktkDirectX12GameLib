#include "TktkDX12BaseComponents/2D/InertialMovement2D/InertialMovement2DMaker.h"

namespace tktk
{
	InertialMovement2DMaker InertialMovement2DMaker::m_self;

	InertialMovement2DMaker & InertialMovement2DMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = InertialMovement2DMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	InertialMovement2DMaker& InertialMovement2DMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = InertialMovement2DMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 引数の追加階層を設定
		m_self.m_targetState = targetState;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<InertialMovement2D> InertialMovement2DMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.hierarchy.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<InertialMovement2D>(
				m_decelerationPerSec,
				m_initVelocity
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<InertialMovement2D>(
			m_decelerationPerSec,
			m_initVelocity
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	InertialMovement2DMaker & InertialMovement2DMaker::decelerationPerSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_decelerationPerSec = value;
		return *this;
	}

	InertialMovement2DMaker & InertialMovement2DMaker::initVelocity(const tktkMath::Vector2 & value)
	{
		// 値を設定して自身の参照を返す
		m_initVelocity = value;
		return *this;
	}
}