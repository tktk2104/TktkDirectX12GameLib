#include "TktkDX12Game/DXGameResource/OtherResouse/Sound/SoundData.h"

#include <stdexcept>
#include "TktkDX12Game/DXGameResource/OtherResouse/Sound/SoundPlayState.h"

namespace tktk
{
	// 書き込み可能なサウンドバッファの数
	constexpr unsigned int CanWriteBufferQueueNum = 4U;

	// サウンドバッファの総数
	constexpr unsigned int TotalBufferQueueNum = CanWriteBufferQueueNum + 1U;

	SoundData::SoundData(const std::string & fileName, IXAudio2* xAudioPtr, HANDLE hEvent)
		: m_cSoundCallback(CSoundCallback(hEvent))
	{
		// サウンドデータを読み込む
		loadSound(fileName);

		// 読み込んだサウンドデータからソースボイスを作る
		HRESULT hr = xAudioPtr->CreateSourceVoice(&m_lpSourceVoice, &m_wfx, XAUDIO2_VOICE_NOPITCH, XAUDIO2_DEFAULT_FREQ_RATIO, &m_cSoundCallback, NULL, NULL);

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
		, m_cSoundCallback(other.m_cSoundCallback)
		, m_lpSourceVoice(other.m_lpSourceVoice)
		, m_bufferSize(other.m_bufferSize)
		, m_bufferData(std::move(other.m_bufferData))
		, m_soundPlayState(other.m_soundPlayState)
		, m_nextBufferWriteIndex(other.m_nextBufferWriteIndex)
		, m_sumLoadSize(other.m_sumLoadSize)
		, m_sumDataSize(other.m_sumDataSize)
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

		// サウンドファイルの読み込み位置を頭に戻す（今まで読み込んだサウンドファイルの合計サイズ分だけ読み込み位置を戻す）
		mmioSeek(m_hmmio, -static_cast<long>(m_sumLoadSize), SEEK_CUR);

		// 今まで読み込んだサウンドファイルの合計を初期化する
		m_sumLoadSize = 0U;

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
		// サウンド再生フラグが立っていなかったらサウンドの更新を行わない
		if ((m_soundPlayState & SoundPlayState::Playing) == 0U) return;

		// 現在のサウンドの状態を取得する
		XAUDIO2_VOICE_STATE voiceState;
		m_lpSourceVoice->GetState(&voiceState);

		// サウンドバッファを読み込む余裕があったら読み込む
		while (voiceState.BuffersQueued < CanWriteBufferQueueNum && m_hmmio != nullptr)
		{
			// これからサウンドデータを読み込み、書き込むメモリアドレスを求める
			unsigned char* bufLoadTopPtr = m_bufferData.data() + m_bufferSize * m_nextBufferWriteIndex;

			// 書き込みインデックスを更新する
			m_nextBufferWriteIndex = (m_nextBufferWriteIndex + 1) % TotalBufferQueueNum;

			// 読み込むデータの大きさ
			auto loadDataSize = m_bufferSize;

			// サウンドの読み込みが終わったか？
			bool soundLoadEnd = false;

			// サウンドデータをオーバーして読み込もうとした場合、
			if ((m_sumLoadSize + loadDataSize) >= m_sumDataSize)
			{
				// 読み込むデータの大きさを補正する
				loadDataSize = m_sumDataSize - m_sumLoadSize;

				// サウンドの読み込みを終えるフラグを立てる
				soundLoadEnd = true;
			}

			// 読み込むデータが存在しなかったら
			if (loadDataSize == 0U)
			{
				if (voiceState.BuffersQueued == 0U)
				{
					// 停止する前のサウンド再生状態を保持する
					auto preSoundPlayState = m_soundPlayState;

					// サウンドを停止する
					stopSound();

					// ループフラグが立っていたら再度再生する
					if ((preSoundPlayState & SoundPlayState::Loop) != 0) playSound(true);
				}
				// 読み込みループを抜ける
				break;
			}

			// サウンドバッファを更新し、更新したバッファサイズを取得する
			auto resultLoadDataSize = mmioRead(m_hmmio, reinterpret_cast<HPSTR>(bufLoadTopPtr), loadDataSize);

			// 実際に読み込んだデータサイズが読み込みサイズと違った場合、何かしらの問題が発生している
			if (resultLoadDataSize != loadDataSize)
			{
				throw std::runtime_error("load sound buffer error");
			}

			// 今まで読み込んだサウンドバッファの大きさを更新する
			m_sumLoadSize += loadDataSize;

			// ソースボイスにデータを転送する為のパラメータ
			XAUDIO2_BUFFER bufinfo;
			memset(&bufinfo, 0x00, sizeof(XAUDIO2_BUFFER));

			// サウンドの読み込みが終了していたらストリーム終了フラグを立てる
			bufinfo.Flags = (soundLoadEnd) ? XAUDIO2_END_OF_STREAM : 0;
			// 転送するバッファの大きさ
			bufinfo.AudioBytes	= loadDataSize;
			// 転送するバッファの読み込み開始位置
			bufinfo.pAudioData	= bufLoadTopPtr;
			// 転送したバッファのどこから再生するか？（小分けで転送する関係上常に０）
			bufinfo.PlayBegin	= 0;
			// 転送したバッファの総再生量
			bufinfo.PlayLength	= loadDataSize / m_wfx.nBlockAlign;

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
			// 小さいサイズ版フォーマットデータ
			PCMWAVEFORMAT	pcmwf;

			mmioRead(m_hmmio, (HPSTR)&pcmwf, sizeof(PCMWAVEFORMAT));
			memset(&m_wfx, 0x00, sizeof(WAVEFORMATEX));
			memcpy(&m_wfx, &pcmwf, sizeof(PCMWAVEFORMAT));
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
	
		// サウンドデータの大きさを保存する（バイト）
		m_sumDataSize = dataChunkInfo.cksize;
	}

	void SoundData::initSound()
	{
		// サウンドバッファの大きさを0.25秒間のサウンドデータの大きさに設定する
		m_bufferSize = m_wfx.nAvgBytesPerSec / 4;

		// サウンドバッファを書き込む領域を「BufferQueueAlloc」の数だけ作る
		m_bufferData.resize(m_bufferSize * TotalBufferQueueNum);

		// サウンドバッファを読み込む位置
		unsigned char* bufLoadTopPtr = m_bufferData.data();

		auto tempBuflen = m_bufferSize;

		bool endSound = false;

		// サウンドデータをオーバーしてバッファの読み込みを行おうとした場合、読み込み範囲を修正する
		if (tempBuflen >= m_sumDataSize)
		{
			tempBuflen = m_sumDataSize;
			endSound = true;
		}

		// サウンドバッファを更新し、更新したバッファサイズを取得する
		auto readlen = mmioRead(m_hmmio, (HPSTR)bufLoadTopPtr, tempBuflen);

		// サウンドバッファを更新エラーチェック
		if (readlen <= 0) throw std::runtime_error("load sound buffer error");

		// サウンドカウンターを初期化
		m_nextBufferWriteIndex = 1u;

		// 今まで読み込んだサウンドバッファの長さを初期化
		m_sumLoadSize = readlen;

		// ソースボイスにデータを転送する為のパラメータ
		XAUDIO2_BUFFER bufinfo;
		memset(&bufinfo, 0x00, sizeof(XAUDIO2_BUFFER));

		// 更新したバッファの長さが想定よりも短い（読み込むバッファがもうない）のであれば「XAUDIO2_END_OF_STREAM」フラグを立てる
		bufinfo.Flags = (endSound) ? XAUDIO2_END_OF_STREAM : 0;
		// 転送するバッファの長さ
		bufinfo.AudioBytes = readlen;
		// 転送するバッファの読み込み開始位置
		bufinfo.pAudioData = bufLoadTopPtr;
		// 転送したバッファのどこから再生するか？（小分けで転送する関係上常に０）
		bufinfo.PlayBegin = 0;
		// 転送したバッファの総再生量
		bufinfo.PlayLength = readlen / m_wfx.nBlockAlign;

		// ソースボイスにデータを転送する
		HRESULT hr = m_lpSourceVoice->SubmitSourceBuffer(&bufinfo, nullptr);

		// ソースボイスへのデータ転送エラーチェック
		if (FAILED(hr)) throw std::runtime_error("submit source buffer error");
	}
}