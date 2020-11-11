#ifndef SOUND_H_
#define SOUND_H_

/* IXAudio2, IXAudio2MasteringVoice, HANDLE */
#include <xaudio2.h>
#undef min
#undef max

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

namespace tktk
{
	class SoundData;

	// 「SoundData」を管理するクラス
	class SoundManager
	{
	public:

		explicit SoundManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~SoundManager();

		SoundManager(const SoundManager& other) = delete;
		SoundManager& operator = (const SoundManager& other) = delete;

	public:

		void update();

	public:

		// 新たなサウンドをロードし、そのリソースのハンドルを返す
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		size_t load(const std::string& fileName);

		// 全てのサウンドを削除する
		void clear();

		// 指定したサウンドを再生する
		void play(size_t handle, bool loopPlay);

		// 指定したサウンドを停止する
		void stop(size_t handle);

		// 指定したサウンドを一時停止する
		void pause(size_t handle);

		// 大元の音量を変更する（0.0f～1.0f）
		void setMasterVolume(float volume);

	private:

		tktkContainer::ResourceContainer<SoundData> m_assets;

		// サウンドのイベント処理に使用する変数
		HANDLE m_soundEvent{ NULL };

		// XAudioのポインタ
		IXAudio2* m_xAudioPtr{ NULL };

		// マスタリングボイスのポインタ
		IXAudio2MasteringVoice* m_masterVoicePtr{ NULL };
	};
}
#endif // !SOUND_H_