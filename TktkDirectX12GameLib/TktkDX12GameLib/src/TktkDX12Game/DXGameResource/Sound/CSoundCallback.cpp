#include "TktkDX12Game/DXGameResource/Sound/CSoundCallback.h"

namespace tktk
{
	CSoundCallback::CSoundCallback(HANDLE hEvent)
		: m_hEvent(hEvent)
	{
	}

	CSoundCallback::~CSoundCallback()
	{
	}

	void __stdcall CSoundCallback::OnVoiceProcessingPassStart(UINT32 BytesRequired)
	{
	}

	void __stdcall CSoundCallback::OnVoiceProcessingPassEnd()
	{
	}

	void __stdcall CSoundCallback::OnStreamEnd()
	{
		SetEvent(m_hEvent);
	}

	void __stdcall CSoundCallback::OnBufferStart(void * pBufferContext)
	{
		SetEvent(m_hEvent);
	}

	void __stdcall CSoundCallback::OnBufferEnd(void * pBufferContext)
	{
	}

	void __stdcall CSoundCallback::OnLoopEnd(void * pBufferContext)
	{
	}

	void __stdcall CSoundCallback::OnVoiceError(void * pBufferContext, HRESULT Error)
	{
	}
}