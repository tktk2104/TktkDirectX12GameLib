#ifndef SOUND_DATA_H_
#define SOUND_DATA_H_

#include <string>
#include <vector>
#include <xaudio2.h>
#undef min
#undef max
#include "CSoundCallback.h"

namespace tktk
{
	// サウンドを管理するクラス
	class SoundData
	{
	public:

		SoundData(const std::string& fileName, IXAudio2* xAudioPtr, HANDLE hEvent);
		~SoundData();

		SoundData(const SoundData& other) = delete;
		SoundData& operator = (const SoundData& other) = delete;

		// ムーブコンストラクタ
		SoundData(SoundData&& other) noexcept;

	public:

		// サウンドを再生しているか？
		bool isPlaySound() const;

		// サウンドの再生を開始
		void playSound(bool loopPlay);

		// サウンドを再生を停止
		void stopSound();

		// サウンドの再生を一時停止
		void pauseSound();

		void update();

	private:

		void loadSound(const std::string& fileName);

		void initSound();

	private:

		// wavファイルのハンドル
		HMMIO			m_hmmio{ nullptr };
		
		// wavファイルのフォーマット情報
		WAVEFORMATEX	m_wfx;
		// フォーマットチャンクが大きすぎる時に使用される情報
		PCMWAVEFORMAT	m_pcmwf;

		// サウンドのコールバック処理クラス
		CSoundCallback m_cSoundCallback;

		// ソースボイス
		IXAudio2SourceVoice* m_lpSourceVoice{ nullptr };

		// サウンドバッファの大きさ
		unsigned int m_buflen;

		// サウンドバッファ（0.25秒間のサウンドデータを持つ５つのサウンドバッファが連続して存在している）
		std::vector<unsigned char> m_bufData;

		// サウンド再生の状態を表すビットフラグ
		unsigned int m_soundPlayState{ 0U };

		// 音楽再生用のカウンタ
		unsigned int m_soundCount;

		// サウンドバッファを読み込んだ総数
		unsigned int m_sumReadlen;
	};
}
#endif // !SOUND_DATA_H_