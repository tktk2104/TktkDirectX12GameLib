#include "TktkDX12BaseComponents/Other/Sound/SoundPlayerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	SoundPlayerMaker SoundPlayerMaker::m_self;

	SoundPlayerMaker& SoundPlayerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = SoundPlayerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<SoundPlayer> SoundPlayerMaker::create()
	{
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<SoundPlayer>(
			m_soundHandle,
			m_isLoop,
			m_startToPlay
			);
	}

	SoundPlayerMaker& SoundPlayerMaker::soundHandle(size_t value)
	{
		m_soundHandle = value;
		return *this;
	}

	SoundPlayerMaker& SoundPlayerMaker::soundId(ResourceIdCarrier value)
	{
		m_soundHandle = DX12GameManager::getSoundHandle(value);
		return *this;
	}

	SoundPlayerMaker& SoundPlayerMaker::isLoop(bool value)
	{
		m_isLoop = value;
		return *this;
	}

	SoundPlayerMaker& SoundPlayerMaker::startToPlay(bool value)
	{
		m_startToPlay = value;
		return *this;
	}
}