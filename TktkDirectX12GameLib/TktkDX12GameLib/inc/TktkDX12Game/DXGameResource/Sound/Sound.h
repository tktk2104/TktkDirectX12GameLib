#ifndef SOUND_H_
#define SOUND_H_

#include <xaudio2.h>
#undef min
#undef max
#include <TktkContainer/HeapArray/HeapArray.h>
#include "SoundData.h"

namespace tktk
{
	// 「SoundData」を管理するクラス
	class Sound
	{
	public:

		Sound(unsigned int soundDataNum);
		~Sound();

		Sound(const Sound& other) = delete;
		Sound& operator = (const Sound& other) = delete;

	public:

		void update();

	public:

		// 新たなサウンドをロードする
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		void load(unsigned int id, const std::string& fileName);

		// 全てのサウンドを削除する
		void clear();

		// 指定したサウンドを再生する
		void play(unsigned int id, bool loopPlay);

		// 指定したサウンドを停止する
		void stop(unsigned int id);

		// 指定したサウンドを一時停止する
		void pause(unsigned int id);

		// 大元の音量を変更する（0.0f～1.0f）
		void setMasterVolume(float volume);

	private:

		tktkContainer::HeapArray<SoundData> m_assets;

		// サウンドのイベント処理に使用する変数
		HANDLE m_soundEvent{ NULL };

		// XAudioのポインタ
		IXAudio2* m_xAudioPtr{ NULL };

		// マスタリングボイスのポインタ
		IXAudio2MasteringVoice* m_masterVoicePtr{ NULL };
	};
}
#endif // !SOUND_H_