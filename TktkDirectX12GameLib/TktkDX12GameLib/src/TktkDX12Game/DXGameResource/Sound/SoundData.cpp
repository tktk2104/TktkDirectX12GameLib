#include "TktkDX12Game/DXGameResource/Sound/SoundData.h"

#include <stdexcept>
#include "TktkDX12Game/DXGameResource/Sound/SoundPlayState.h"

namespace tktk
{
	// サウンドバッファの最大数
	constexpr unsigned int BufferQueueMax = 4U;

	// 実際に作るサウンドバッファの数
	constexpr unsigned int BufferQueueAlloc = BufferQueueMax + 1U;

	SoundData::SoundData(const std::string & fileName, IXAudio2* xAudioPtr, HANDLE hEvent)
		: m_cSoundCallback(CSoundCallback(hEvent))
	{
		loadSound(fileName);

		HRESULT hr = xAudioPtr->CreateSourceVoice(
			&m_lpSourceVoice, &m_wfx, XAUDIO2_VOICE_NOPITCH, XAUDIO2_DEFAULT_FREQ_RATIO, &m_cSoundCallback, NULL, NULL
		);

		if (FAILED(hr)) throw std::runtime_error("create sourceVoice error");
	}

	SoundData::~SoundData()
	{
		stopSound();
		update();

		if (m_lpSourceVoice != nullptr)
			m_lpSourceVoice->DestroyVoice();

		if (m_hmmio != nullptr)
			mmioClose(m_hmmio, 0);
	}

	SoundData::SoundData(SoundData&& other) noexcept
		: m_hmmio(other.m_hmmio)
		, m_wfx(other.m_wfx)
		, m_pcmwf(other.m_pcmwf)
		, m_cSoundCallback(other.m_cSoundCallback)
		, m_lpSourceVoice(other.m_lpSourceVoice)
		, m_buflen(other.m_buflen)
		, m_bufData(std::move(other.m_bufData))
		, m_soundPlayState(other.m_soundPlayState)
		, m_soundCount(other.m_soundCount)
		, m_sumReadlen(other.m_sumReadlen)
	{
		m_lpSourceVoice = nullptr;
		m_hmmio			= nullptr;
	}

	bool SoundData::isPlaySound() const
	{
 		return ((m_soundPlayState & SoundPlayState::Playing) != 0) && ((m_soundPlayState & SoundPlayState::Pause) == 0);
	}

	void SoundData::playSound(bool loopPlay)
	{
		// ループ再生を行う場合はループフラグを立てる
		if (loopPlay) m_soundPlayState |= SoundPlayState::Loop;

		// サウンドが既に再生中だったら一旦停止する
		if ((m_soundPlayState & SoundPlayState::Playing) != 0) stopSound();

		// ポーズ中フラグが立っていなければサウンドの再生状況を初期化する
		if ((m_soundPlayState & SoundPlayState::Pause) == 0) initSound();

		// サウンドの再生を開始する
		HRESULT hr = m_lpSourceVoice->Start(0, XAUDIO2_COMMIT_NOW);

		// 再生エラーチェック
		if (FAILED(hr)) throw std::runtime_error("play sound error");

		// ポーズ中フラグを折る
		m_soundPlayState &= (~SoundPlayState::Pause);

		// 再生中フラグを立てる
		m_soundPlayState |= SoundPlayState::Playing;
	}

	void SoundData::stopSound()
	{
		// ソースバッファをフラッシュする
		m_lpSourceVoice->FlushSourceBuffers();

		// サウンドファイルの読み込み位置を頭に戻す
		mmioSeek(m_hmmio, -static_cast<long>(m_sumReadlen), SEEK_CUR);

		// サウンド再生フラグを初期化する
		m_soundPlayState = 0U;
	}

	void SoundData::pauseSound()
	{
		// サウンドを停止する
		m_lpSourceVoice->Stop();

		// ポーズ中フラグを立てる
		m_soundPlayState |= SoundPlayState::Pause;
	}

	void SoundData::update()
	{
		// 現在のサウンドの状態を取得する
		XAUDIO2_VOICE_STATE voiceState;
		m_lpSourceVoice->GetState(&voiceState);

		// 現在読み込んでいるサウンドバッファが０だったら下の処理をスキップする
		if (voiceState.BuffersQueued == 0) return;

		// サウンドバッファを読み込む余裕があったら読み込む
		while (voiceState.BuffersQueued < BufferQueueMax && m_hmmio != nullptr)
		{
			// サウンドバッファ読み込み位置を更新する
			unsigned char* bufLoadTopPtr = m_bufData.data() + m_buflen * m_soundCount;

			// サウンドカウンターを更新する
			m_soundCount = (m_soundCount + 1) % BufferQueueAlloc;

			// サウンドバッファを更新し、更新したバッファサイズを取得する
			auto readlen = mmioRead(m_hmmio, reinterpret_cast<HPSTR>(bufLoadTopPtr), m_buflen);

			// 更新したバッファサイズが０以下だったら
			if (readlen <= 0)
			{
				// 停止する前のサウンド再生状態を保持する
				auto preSoundPlayState = m_soundPlayState;

				// サウンドを停止する
				stopSound();

				// ループフラグが立っていたら再度再生する
				if ((preSoundPlayState & SoundPlayState::Loop) != 0) playSound(true);

				// 読み込みループを抜ける
				break;
			}
			
			// 今まで読み込んだサウンドバッファの長さを更新する
			m_sumReadlen += readlen;

			// ソースボイスにデータを転送する為のパラメータ
			XAUDIO2_BUFFER bufinfo;
			memset(&bufinfo, 0x00, sizeof(XAUDIO2_BUFFER));

			// 更新したバッファの長さが想定よりも短い（読み込むバッファがもうない）のであれば「XAUDIO2_END_OF_STREAM」フラグを立てる
			bufinfo.Flags		= (static_cast<unsigned int>(readlen) >= m_buflen) ? 0 : XAUDIO2_END_OF_STREAM;
			// 転送するバッファの長さ
			bufinfo.AudioBytes	= readlen;
			// 転送するバッファの読み込み開始位置
			bufinfo.pAudioData	= bufLoadTopPtr;
			// 転送したバッファのどこから再生するか？（小分けで転送する関係上常に０）
			bufinfo.PlayBegin	= 0;
			// 転送したバッファの総再生量
			bufinfo.PlayLength	= readlen / m_wfx.nBlockAlign;

			// ソースボイスにデータを転送する
			HRESULT hr = m_lpSourceVoice->SubmitSourceBuffer(&bufinfo, nullptr);

			// ソースボイスへのデータ転送エラーチェック
			if (FAILED(hr)) throw std::runtime_error("submit source buffer error");

			// バッファキューをインクリメント
			voiceState.BuffersQueued++;
		}
	}

	void SoundData::loadSound(const std::string & fileName)
	{
#ifdef _M_AMD64 /* x64ビルドなら */

		std::wstring wstrFileName = std::wstring(fileName.begin(), fileName.end());
		const TCHAR* lpFileName = wstrFileName.c_str();
#else
		const TCHAR* lpFileName = TEXT(fileName.c_str());
#endif // _M_AMD64

		// リフ構造ファイルを読み込む時に使用するMMIO情報データ構造
		MMIOINFO	mmioInfo;
		// リフ構造ファイルを読み込む時に使用するRIFFチャンク情報データ構造（wavチャンク用）
		MMCKINFO	riffChunkInfo;
		// リフ構造ファイルを読み込む時に使用するRIFFチャンク情報データ構造（フォーマットチャンク用）
		MMCKINFO	formatChunkInfo;
		// リフ構造ファイルを読み込む時に使用するRIFFチャンク情報データ構造（データチャンク用）
		MMCKINFO	dataChunkInfo;

		// エラー検知用変数
		MMRESULT	mmret;

		// MMIOデータ構造情報をゼロクリア
		memset(&mmioInfo, 0x00, sizeof(MMIOINFO));

		// MMIOデータ構造情報を読み込む
		m_hmmio = mmioOpen(const_cast<TCHAR *>(lpFileName), &mmioInfo, MMIO_READ);

		// 読み込みエラーチェック
		if (m_hmmio == NULL) throw std::runtime_error("load sound error");

		// RIFF形式のWAVEチャンク構造情報をゼロクリア
		memset(&riffChunkInfo, 0x00, sizeof(MMCKINFO));

		// WAVEチャンクに移動するための情報を設定
		riffChunkInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');

		// WAVEチャンクに移動
		mmret = mmioDescend(m_hmmio, &riffChunkInfo, NULL, MMIO_FINDRIFF);

		// チャンク移動エラーチェック
		if (mmret != MMSYSERR_NOERROR) throw std::runtime_error("load sound error");

		// RIFF形式のフォーマットチャンク構造情報をゼロクリア
		memset(&formatChunkInfo, 0x00, sizeof(MMCKINFO));

		// フォーマットチャンクに移動するための情報を設定
		formatChunkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');

		// WAVEチャンクからフォーマットチャンクに移動
		mmret = mmioDescend(m_hmmio, &formatChunkInfo, &riffChunkInfo, MMIO_FINDCHUNK);

		// チャンク移動エラーチェック
		if (mmret != MMSYSERR_NOERROR) throw std::runtime_error("load sound error");

		// TODO : ここの処理の意味を理解する
		if (formatChunkInfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(m_hmmio, (HPSTR)&m_wfx, sizeof(WAVEFORMATEX));
		}
		else
		{
			mmioRead(m_hmmio, (HPSTR)&m_pcmwf, sizeof(PCMWAVEFORMAT));
			memset(&m_wfx, 0x00, sizeof(WAVEFORMATEX));
			memcpy(&m_wfx, &m_pcmwf, sizeof(PCMWAVEFORMAT));
			m_wfx.cbSize = 0;
		}
		
		// フォーマットチャンクからWAVEチャンクに戻る
		mmioAscend(m_hmmio, &formatChunkInfo, 0);

		// RIFF形式のデータチャンク構造情報をゼロクリア
		memset(&dataChunkInfo, 0x00, sizeof(MMCKINFO));

		// データチャンクに移動するための情報を設定
		dataChunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');

		// WAVEチャンクからデータチャンクに移動
		mmret = mmioDescend(m_hmmio, &dataChunkInfo, &riffChunkInfo, MMIO_FINDCHUNK);

		// チャンク移動エラーチェック
		if (mmret != MMSYSERR_NOERROR) throw std::runtime_error("load sound error");
	}

	void SoundData::initSound()
	{
		// サウンドバッファの大きさを0.25秒間のサウンドデータの大きさに設定する
		m_buflen = m_wfx.nAvgBytesPerSec / 4;

		// サウンドバッファを書き込む領域を「BufferQueueAlloc」の数だけ作る
		m_bufData.resize(m_buflen * BufferQueueAlloc);

		// サウンドバッファを読み込む位置
		unsigned char* bufLoadTopPtr = m_bufData.data();

		// サウンドバッファを更新し、更新したバッファサイズを取得する
		auto readlen = mmioRead(m_hmmio, (HPSTR)bufLoadTopPtr, m_buflen);

		// サウンドバッファを更新エラーチェック
		if (readlen <= 0) throw std::runtime_error("load sound buffer error");

		// サウンドカウンターを初期化
		m_soundCount = 1u;

		// 今まで読み込んだサウンドバッファの長さを初期化
		m_sumReadlen = readlen;

		// ソースボイスにデータを転送する為のパラメータ
		XAUDIO2_BUFFER bufinfo;
		memset(&bufinfo, 0x00, sizeof(XAUDIO2_BUFFER));

		// 更新したバッファの長さが想定よりも短い（読み込むバッファがもうない）のであれば「XAUDIO2_END_OF_STREAM」フラグを立てる
		bufinfo.Flags = ((UINT32)readlen >= m_buflen) ? 0 : XAUDIO2_END_OF_STREAM;
		// 転送するバッファの長さ
		bufinfo.AudioBytes = readlen;
		// 転送するバッファの読み込み開始位置
		bufinfo.pAudioData = bufLoadTopPtr;
		// 転送したバッファのどこから再生するか？（小分けで転送する関係上常に０）
		bufinfo.PlayBegin = 0;
		// 転送したバッファの総再生量
		bufinfo.PlayLength = readlen / m_wfx.nBlockAlign;

		// ソースボイスにデータを転送する
		HRESULT hr = m_lpSourceVoice->SubmitSourceBuffer(&bufinfo, NULL);

		// ソースボイスへのデータ転送エラーチェック
		if (FAILED(hr)) throw std::runtime_error("submit source buffer error");
	}
}