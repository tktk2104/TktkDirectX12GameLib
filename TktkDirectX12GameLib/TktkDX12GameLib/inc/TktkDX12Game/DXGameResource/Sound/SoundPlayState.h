#ifndef SOUND_PLAY_STATE_H_
#define SOUND_PLAY_STATE_H_

namespace tktk
{
	enum SoundPlayState
	{
		SOUND_PLAY_STATE_PLAYING	= 1 << 0,
		SOUND_PLAY_STATE_PAUSE		= 1 << 1,
		SOUND_PLAY_STATE_LOOP		= 1 << 2
	};
}
#endif // !SOUND_PLAY_STATE_H_