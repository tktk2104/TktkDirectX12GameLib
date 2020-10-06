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

	ComponentPtr<SoundPlayer> SoundPlayerMaker::create()
	{
		return m_user->createComponent<SoundPlayer>(
			m_soundHandle,
			m_isLoop,
			m_startToPlay
			);
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