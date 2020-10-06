#ifndef SOUND_PLAY_STATE_H_
#define SOUND_PLAY_STATE_H_

namespace tktk
{
	struct SoundPlayState
	{
		static constexpr unsigned int Playing	= 1 << 0;
		static constexpr unsigned int Pause		= 1 << 1;
		static constexpr unsigned int Loop		= 1 << 2;
	};
}
#endif // !SOUND_PLAY_STATE_H_