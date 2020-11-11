#include"TktkDX12BaseComponents/3D/Camera/FirstPersonModuleMaker.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

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

	ComponentPtr<FirstPersonModule> FirstPersonModuleMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<FirstPersonModule>(
			m_rotateDegSpeedPerSec,
			m_moveSpeedPerSec,
			m_alwaysMoveForward,
			m_enableUpDownKey
			);
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