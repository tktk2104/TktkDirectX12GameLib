#ifndef SOUND_PLAY_TIMER_H_
#define SOUND_PLAY_TIMER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	class SoundPlayTimer
		: public ComponentBase
	{
	public:

		SoundPlayTimer(size_t handle, float firstPlayStartTimeSec, float playIntervalSec, int playCount, bool startToPlay);

	public:

		void startPlayTimer();

		void stopPlayTimer();

	public:

		void onEnable();

		void update();

	private:

		bool	m_isStartSecTimer;
		float	m_soundPlayTimer;
		int		m_playCounter{ 0 };

		size_t	m_soundHandle;
		float	m_firstPlayStartTimeSec;
		float	m_playIntervalSec;
		int		m_playCount;
		bool	m_startToPlay;
	};
}
#endif // !SOUND_PLAY_TIMER_H_