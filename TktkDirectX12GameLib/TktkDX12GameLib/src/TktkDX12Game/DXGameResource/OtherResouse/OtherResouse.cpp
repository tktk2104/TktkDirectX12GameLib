#include "TktkDX12Game/DXGameResource/OtherResouse/OtherResouse.h"

#include "TktkDX12Game/DXGameResource/OtherResouse/Structs/OtherResouseInitParam.h"
#include "TktkDX12Game/DXGameResource/OtherResouse/Scene/SceneManager.h"
#include "TktkDX12Game/DXGameResource/OtherResouse/Sound/SoundManager.h"
#include "TktkDX12Game/DXGameResource/OtherResouse/Font/FontManager.h"

namespace tktk
{
	OtherResouse::OtherResouse(const OtherResouseInitParam& initParam)
	{
		m_sceneManager	= std::make_unique<SceneManager>(initParam.sceneMgrParam);
		m_soundManager	= std::make_unique<SoundManager>(initParam.soundMgrParam);
		m_fontManager	= std::make_unique<FontManager>(initParam.fontMgrParam, initParam.textTextureSize);
	}

	// デストラクタを非インライン化する
	OtherResouse::~OtherResouse() = default;

	void OtherResouse::update()
	{
		m_sceneManager->update();
		m_soundManager->update();
	}

	size_t OtherResouse::createScene(const SceneInitParam& initParam)
	{
		return m_sceneManager->create(initParam);
	}

	void OtherResouse::setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag)
	{
		m_sceneManager->setSceneEndDestroyGameObjectTag(handle, tag);
	}

	void OtherResouse::enableScene(size_t handle)
	{
		m_sceneManager->enable(handle);
	}

	void OtherResouse::disableScene(size_t handle)
	{
		m_sceneManager->disable(handle);
	}

	void OtherResouse::clearSound()
	{
		m_soundManager->clear();
	}

	size_t OtherResouse::loadSound(const std::string& fileName)
	{
		return m_soundManager->load(fileName);
	}

	void OtherResouse::playSound(size_t handle, bool loopPlay)
	{
		m_soundManager->play(handle, loopPlay);
	}

	void OtherResouse::stopSound(size_t handle)
	{
		m_soundManager->stop(handle);
	}

	void OtherResouse::pauseSound(size_t handle)
	{
		m_soundManager->pause(handle);
	}

	void OtherResouse::setMasterVolume(float volume)
	{
		m_soundManager->setMasterVolume(volume);
	}

	void OtherResouse::createFontBaseResource()
	{
		m_fontManager->createFontBaseResource();
	}

	size_t OtherResouse::createFont(const std::string& systemFontName, int fontSize, float fontThicknessRate)
	{
		return m_fontManager->create(systemFontName, fontSize, fontThicknessRate);
	}

	size_t OtherResouse::createFont(const std::string& fontFilePath, const std::string& fontName, int fontSize, float fontThicknessRate)
	{
		return m_fontManager->create(fontFilePath, fontName, fontSize, fontThicknessRate);
	}

	size_t OtherResouse::updateTextTextureUploadBuffData(size_t handle, size_t uploadBufferHandle, const std::string& text)
	{
		return m_fontManager->updateTextTextureUploadBuffData(handle, uploadBufferHandle, text);
	}

	size_t OtherResouse::createTextTextureUploadBuffer()
	{
		return m_fontManager->createUploadBuffer();
	}
}