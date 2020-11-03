#include"TktkDX12BaseComponents/3D/Camera/FirstPersonModuleMaker.h"

namespace tktk
{
	FirstPersonModuleMaker FirstPersonModuleMaker::m_self;

	FirstPersonModuleMaker & FirstPersonModuleMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = FirstPersonModuleMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	FirstPersonModuleMaker& FirstPersonModuleMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = FirstPersonModuleMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 引数の追加階層を設定
		m_self.m_targetState = targetState;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<FirstPersonModule> FirstPersonModuleMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.hierarchy.empty())
		{
			return m_user->createComponent<FirstPersonModule>(
				m_rotateDegSpeedPerSec,
				m_moveSpeedPerSec,
				m_alwaysMoveForward,
				m_enableUpDownKey
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<FirstPersonModule>(
			m_rotateDegSpeedPerSec,
			m_moveSpeedPerSec,
			m_alwaysMoveForward,
			m_enableUpDownKey
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	FirstPersonModuleMaker & FirstPersonModuleMaker::rotateDegSpeedPerSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_rotateDegSpeedPerSec = value;
		return *this;
	}

	FirstPersonModuleMaker & FirstPersonModuleMaker::moveSpeedPerSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_moveSpeedPerSec = value;
		return *this;
	}

	FirstPersonModuleMaker & FirstPersonModuleMaker::alwaysMoveForward(bool value)
	{
		// 値を設定して自身の参照を返す
		m_alwaysMoveForward = value;
		return *this;
	}

	FirstPersonModuleMaker & FirstPersonModuleMaker::enableUpDownKey(bool value)
	{
		// 値を設定して自身の参照を返す
		m_enableUpDownKey = value;
		return *this;
	}
}