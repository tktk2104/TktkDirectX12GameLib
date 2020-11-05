#include "TktkDX12BaseComponents/Other/Sound/SoundPlayer.h"

namespace tktk
{
	SoundPlayer::SoundPlayer(size_t soundHandle, bool isLoop, bool startToPlay)
		: m_soundHandle(soundHandle)
		, m_isLoop(isLoop)
		, m_startToPlay(startToPlay)
	{
	}

	void SoundPlayer::playSound()
	{
		DX12GameManager::playSound(m_soundHandle, m_isLoop);
	}

	void SoundPlayer::stopSound()
	{
		DX12GameManager::stopSound(m_soundHandle);
	}

	void SoundPlayer::pauseSound()
	{
		DX12GameManager::pauseSound(m_soundHandle);
	}

	void SoundPlayer::changeSoundHandle(size_t soundHandle)
	{
		m_soundHandle = soundHandle;

		playSound();
	}

	void SoundPlayer::changeSoundId(ResourceIdCarrier soundId)
	{
		m_soundHandle = DX12GameManager::getSoundHandle(soundId);

		playSound();
	}

	void SoundPlayer::start()
	{
		if (m_startToPlay)
		{
			DX12GameManager::playSound(m_soundHandle, m_isLoop);
		}
	}

	void SoundPlayer::onEnable()
	{
		DX12GameManager::playSound(m_soundHandle, m_isLoop);
	}

	void SoundPlayer::onDisable()
	{
		DX12GameManager::stopSound(m_soundHandle);
	}

	void SoundPlayer::onDestroy()
	{
		DX12GameManager::stopSound(m_soundHandle);
	}
}