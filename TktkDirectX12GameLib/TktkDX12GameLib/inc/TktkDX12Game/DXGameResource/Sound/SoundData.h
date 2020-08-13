#ifndef SOUND_DATA_H_
#define SOUND_DATA_H_

#include <string>
#include <vector>
#include <xaudio2.h>
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
		HMMIO			m_hmmio{ NULL };
		// リフ構造ファイルを読み込む時に使用するMMIO情報データ構造
		MMIOINFO		m_mmioInfo;
		// リフ構造ファイルを読み込む時に使用するRIFFチャンク情報データ構造（wavチャンク用）
		MMCKINFO		m_riffChunkInfo;
		// リフ構造ファイルを読み込む時に使用するRIFFチャンク情報データ構造（フォーマットチャンク用）
		MMCKINFO		m_formatChunkInfo;
		// リフ構造ファイルを読み込む時に使用するRIFFチャンク情報データ構造（データチャンク用）
		MMCKINFO		m_dataChunkInfo;

		// wavファイルのフォーマット情報
		WAVEFORMATEX	m_wfx;
		// フォーマットチャンクが大きすぎる時に使用される情報
		PCMWAVEFORMAT	m_pcmwf;

		// サウンドのコールバック処理クラス
		CSoundCallback m_cSoundCallback;

		IXAudio2SourceVoice* m_lpSourceVoice{ nullptr };

		// サウンドバッファのパラメータ
		XAUDIO2_BUFFER m_bufinfo;

		// サウンドの状態
		XAUDIO2_VOICE_STATE m_voiceState;

		// サウンドバッファの大きさ
		unsigned int m_buflen;

		// サウンドバッファ
		std::vector<unsigned char> m_bufData;

		// サウンドバッファを読み込む位置
		unsigned char* m_bufLoadPos;

		// サウンドバッファを読み込む長さ
		long m_readlen;

		// サウンド再生の状態を表すビットフラグ
		unsigned int m_soundPlayState{ 0U };

		// 音楽再生用のカウンタ
		unsigned int m_soundCount;

		// サウンドバッファを読み込んだ総数
		unsigned int m_sumReadlen;
	};
}
#endif // !SOUND_DATA_H_