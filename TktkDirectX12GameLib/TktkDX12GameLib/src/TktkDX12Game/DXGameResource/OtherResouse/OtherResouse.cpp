#include "TktkDX12Game/DXGameResource/OtherResouse/OtherResouse.h"

#include "TktkDX12Game/DXGameResource/OtherResouse/Structs/OtherResouseInitParam.h"
#include "TktkDX12Game/DXGameResource/OtherResouse/Scene/SceneManager.h"
#include "TktkDX12Game/DXGameResource/OtherResouse/Sound/SoundManager.h"

namespace tktk
{
	OtherResouse::OtherResouse(const OtherResouseInitParam& initParam)
	{
		m_sceneManager	= std::make_unique<SceneManager>(initParam.sceneMgrParam);
		m_sound			= std::make_unique<SoundManager>(initParam.soundMgrParam);
	}

	// デストラクタを非インライン化する
	OtherResouse::~OtherResouse() = default;

	void OtherResouse::update()
	{
		m_sceneManager->update();
		m_sound->update();
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
		m_sound->clear();
	}

	size_t OtherResouse::loadSound(const std::string& fileName)
	{
		return m_sound->load(fileName);
	}

	void OtherResouse::playSound(size_t handle, bool loopPlay)
	{
		m_sound->play(handle, loopPlay);
	}

	void OtherResouse::stopSound(size_t handle)
	{
		m_sound->stop(handle);
	}

	void OtherResouse::pauseSound(size_t handle)
	{
		m_sound->pause(handle);
	}

	void OtherResouse::setMasterVolume(float volume)
	{
		m_sound->setMasterVolume(volume);
	}
}