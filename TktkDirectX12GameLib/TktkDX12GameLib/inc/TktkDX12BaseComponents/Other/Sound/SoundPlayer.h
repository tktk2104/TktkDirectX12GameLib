#ifndef SOUND_PLAYER_H_
#define SOUND_PLAYER_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	// サウンド再生コンポーネント
	class SoundPlayer
		: public ComponentBase
	{
	public:

		SoundPlayer(unsigned int soundHandle, bool isLoop, bool startToPlay);

	public:

		void playSound();

		void stopSound();

		void pauseSound();

	public:

		void start();

		void onEnable();

		void onDisable();

		void onDestroy();

	private:

		unsigned int	m_soundHandle;
		bool			m_isLoop;
		bool			m_startToPlay;
	};
}
#endif // !SOUND_PLAYER_H_