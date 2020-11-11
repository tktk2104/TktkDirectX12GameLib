#include "TktkDX12Game/DXGameResource/OtherResouse/Sound/SoundManager.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include "TktkDX12Game/DXGameResource/OtherResouse/Sound/SoundData.h"

namespace tktk
{
	SoundManager::SoundManager(const tktkContainer::ResourceContainerInitParam& initParam)
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

	SoundManager::~SoundManager()
	{
		if (m_soundEvent != NULL)
			CloseHandle(m_soundEvent);

		if (m_masterVoicePtr != NULL)
			m_masterVoicePtr->DestroyVoice();

		if (m_xAudioPtr != NULL)
			m_xAudioPtr->Release();

		CoUninitialize();
	}

	void SoundManager::update()
	{
		DWORD dw = WaitForSingleObject(m_soundEvent, 0LU);

		if (dw != WAIT_OBJECT_0) return;

		for (auto& node : m_assets)
		{
			node.update();
		}
	}

	size_t SoundManager::load(const std::string& fileName)
	{
		return m_assets.create(fileName, m_xAudioPtr, m_soundEvent);
	}

	void SoundManager::clear()
	{
		m_assets.clear();
	}

	void SoundManager::play(size_t handle, bool loopPlay)
	{
		m_assets.getMatchHandlePtr(handle)->playSound(loopPlay);
	}

	void SoundManager::stop(size_t handle)
	{
		if (m_assets.getMatchHandlePtr(handle)->isPlaySound())
		{
			m_assets.getMatchHandlePtr(handle)->stopSound();
		}
	}

	void SoundManager::pause(size_t handle)
	{
		if (m_assets.getMatchHandlePtr(handle)->isPlaySound())
		{
			m_assets.getMatchHandlePtr(handle)->pauseSound();
		}
	}

	void SoundManager::setMasterVolume(float volume)
	{
		volume = tktkMath::MathHelper::clamp(volume, 0.0f, 1.0f);

		m_masterVoicePtr->SetVolume(volume);
	}
}