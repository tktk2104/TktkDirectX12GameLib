#ifndef C_SOUND_CALLBACK_H_
#define C_SOUND_CALLBACK_H_

#include <xaudio2.h>

namespace tktk
{
	// サウンドのコールバック用クラス
	class CSoundCallback
		: public IXAudio2VoiceCallback
	{
	public:

		explicit CSoundCallback(HANDLE hEvent);
		~CSoundCallback();

	public:

		void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 BytesRequired);

		void STDMETHODCALLTYPE OnVoiceProcessingPassEnd();

		void STDMETHODCALLTYPE OnStreamEnd();

		void STDMETHODCALLTYPE OnBufferStart(void *pBufferContext);

		void STDMETHODCALLTYPE OnBufferEnd(void *pBufferContext);

		void STDMETHODCALLTYPE OnLoopEnd(void *pBufferContext);

		void STDMETHODCALLTYPE OnVoiceError(void *pBufferContext, HRESULT Error);

	private:

		HANDLE m_hEvent;
	};
}
#endif // !C_SOUND_CALLBACK_H_
