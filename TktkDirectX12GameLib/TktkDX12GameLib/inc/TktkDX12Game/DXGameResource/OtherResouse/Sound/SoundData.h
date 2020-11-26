#ifndef SOUND_DATA_H_
#define SOUND_DATA_H_

/* std::vector */
#include <vector>

/* HMMIO, WAVEFORMATEX, PCMWAVEFORMAT, IXAudio2SourceVoice */
#include <xaudio2.h>
#undef min
#undef max

/* class member */
#include "CSoundCallback.h"

/* funcUseType */
#include <string>

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

		// サウンドのコールバック処理クラス
		CSoundCallback m_cSoundCallback;

		// ソースボイス
		IXAudio2SourceVoice* m_lpSourceVoice{ nullptr };

		// サウンドバッファ１つあたりの大きさ
		unsigned int m_bufferSize;

		// サウンドバッファ（0.25秒間のサウンドデータを持つ５つのサウンドバッファが連続して存在している）
		std::vector<unsigned char> m_bufferData;

		// サウンド再生の状態を表すビットフラグ
		unsigned int m_soundPlayState{ 0U };

		// 次にサウンドデータを書き込むサウンドバッファインデックス（「bufferTopPtr + (bufferlen * nextBufferWriteIndex)」のアドレスに書き込む）
		unsigned int m_nextBufferWriteIndex;

		// 今まで読み込んだ音声データの合計サイズ
		unsigned int m_sumLoadSize;

		// サウンドデータの合計サイズ
		unsigned int m_sumDataSize;
	};
}
#endif // !SOUND_DATA_H_