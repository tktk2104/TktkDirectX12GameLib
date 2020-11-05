#include "TktkDX12Game/DXGameResource/Sound/Sound.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>

namespace tktk
{
	Sound::Sound(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_assets(initParam)
	{
		auto errorLog = CoInitializeEx(NULL, COINIT_MULTITHREADED);

		m_soundEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (m_soundEvent == NULL)
		{
			throw std::runtime_error("SoundEvent create error");
		}

		HRESULT hr;

		hr = XAudio2Create(&m_xAudioPtr, 0, XAUDIO2_DEFAULT_PROCESSOR);
		if (FAILED(hr))
		{
			throw std::runtime_error("XAudio2 create error");
		}

		hr = m_xAudioPtr->CreateMasteringVoice(&m_masterVoicePtr, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL);
		if (FAILED(hr))
		{
			throw std::runtime_error("MasteringVoice create error");
		}
	}

	Sound::~Sound()
	{
		if (m_soundEvent != NULL)
			CloseHandle(m_soundEvent);

		if (m_masterVoicePtr != NULL)
			m_masterVoicePtr->DestroyVoice();

		if (m_xAudioPtr != NULL)
			m_xAudioPtr->Release();

		CoUninitialize();
	}

	void Sound::update()
	{
		DWORD dw = WaitForSingleObject(m_soundEvent, 0LU);

		if (dw != WAIT_OBJECT_0) return;

		for (auto& node : m_assets)
		{
			node.update();
		}
	}

	size_t Sound::load(const std::string& fileName)
	{
		return m_assets.create(fileName, m_xAudioPtr, m_soundEvent);
	}

	void Sound::clear()
	{
		m_assets.clear();
	}

	void Sound::play(size_t handle, bool loopPlay)
	{
		m_assets.getMatchHandlePtr(handle)->playSound(loopPlay);
	}

	void Sound::stop(size_t handle)
	{
		if (m_assets.getMatchHandlePtr(handle)->isPlaySound())
		{
			m_assets.getMatchHandlePtr(handle)->stopSound();
		}
	}

	void Sound::pause(size_t handle)
	{
		if (m_assets.getMatchHandlePtr(handle)->isPlaySound())
		{
			m_assets.getMatchHandlePtr(handle)->pauseSound();
		}
	}

	void Sound::setMasterVolume(float volume)
	{
		volume = tktkMath::MathHelper::clamp(volume, 0.0f, 1.0f);

		m_masterVoicePtr->SetVolume(volume);
	}
}