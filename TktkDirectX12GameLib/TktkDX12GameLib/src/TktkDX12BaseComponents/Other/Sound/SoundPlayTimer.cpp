#include "TktkDX12BaseComponents/Other/Sound/SoundPlayTimer.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	SoundPlayTimer::SoundPlayTimer(size_t handle, float firstPlayStartTimeSec, float playIntervalSec, int playCount, bool startToPlay)
		: m_soundHandle(handle)
		, m_firstPlayStartTimeSec(firstPlayStartTimeSec)
		, m_playIntervalSec(playIntervalSec)
		, m_playCount(playCount)
		, m_startToPlay(startToPlay)
		, m_isStartSecTimer(startToPlay)
		, m_soundPlayTimer(firstPlayStartTimeSec)
	{
	}

	void SoundPlayTimer::startPlayTimer()
	{
		m_isStartSecTimer	= true;
		m_soundPlayTimer	= m_firstPlayStartTimeSec;
		m_playCounter		= 0;
	}

	void SoundPlayTimer::stopPlayTimer()
	{
		m_isStartSecTimer	= false;
	}

	void SoundPlayTimer::onEnable()
 	{
		m_isStartSecTimer = true;
		m_soundPlayTimer = m_firstPlayStartTimeSec;
		m_playCounter = 0;
	}

	void SoundPlayTimer::update()
	{
		if (!m_isStartSecTimer) return;

		if (m_playCount > 0 && m_playCounter >= m_playCount) return;

		if (m_soundPlayTimer < 0.0f)
		{
			DX12GameManager::playSound(m_soundHandle, false);

			m_soundPlayTimer = m_playIntervalSec;
			if (m_playCount > 0) ++m_playCounter;
			return;
		}

		m_soundPlayTimer -= DX12GameManager::deltaTime();
	}
}