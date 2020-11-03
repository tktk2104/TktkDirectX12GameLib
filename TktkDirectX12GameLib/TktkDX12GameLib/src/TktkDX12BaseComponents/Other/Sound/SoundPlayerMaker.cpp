#include "TktkDX12BaseComponents/Other/Sound/SoundPlayerMaker.h"

namespace tktk
{
	SoundPlayerMaker SoundPlayerMaker::m_self;

	SoundPlayerMaker& SoundPlayerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = SoundPlayerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	SoundPlayerMaker& SoundPlayerMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = SoundPlayerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 引数の追加階層を設定
		m_self.m_targetState = targetState;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<SoundPlayer> SoundPlayerMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.hierarchy.empty())
		{
			return m_user->createComponent<SoundPlayer>(
				m_soundHandle,
				m_isLoop,
				m_startToPlay
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<SoundPlayer>(
			m_soundHandle,
			m_isLoop,
			m_startToPlay
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	SoundPlayerMaker& SoundPlayerMaker::soundHandle(unsigned int value)
	{
		m_soundHandle = value;
		return *this;
	}

	SoundPlayerMaker& SoundPlayerMaker::isLoop(bool value)
	{
		m_isLoop = value;
		return *this;
	}

	SoundPlayerMaker& SoundPlayerMaker::startToPlay(bool value)
	{
		m_startToPlay = value;
		return *this;
	}

	SoundPlayerMaker& SoundPlayerMaker::soundIdImpl(int value)
	{
		m_soundHandle = DX12GameManager::getSoundHandle(value);
		return *this;
	}
}