#include "TktkDX12BaseComponents/Other/Sound/SoundPlayer.h"

namespace tktk
{
	SoundPlayer::SoundPlayer(unsigned int soundId, bool isLoop, bool startToPlay)
		: m_soundId(soundId)
		, m_isLoop(isLoop)
		, m_startToPlay(startToPlay)
	{
	}

	void SoundPlayer::playSound()
	{
		DX12GameManager::playSound(m_soundId, m_isLoop);
	}

	void SoundPlayer::stopSound()
	{
		DX12GameManager::stopSound(m_soundId);
	}

	void SoundPlayer::pauseSound()
	{
		DX12GameManager::pauseSound(m_soundId);
	}

	void SoundPlayer::start()
	{
		if (m_startToPlay)
		{
			DX12GameManager::playSound(m_soundId, m_isLoop);
		}
	}

	void SoundPlayer::onEnable()
	{
		DX12GameManager::playSound(m_soundId, m_isLoop);
	}

	void SoundPlayer::onDisable()
	{
		DX12GameManager::stopSound(m_soundId);
	}

	void SoundPlayer::onDestroy()
	{
		DX12GameManager::stopSound(m_soundId);
	}
}