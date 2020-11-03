#include "TktkDX12BaseComponents/Other/Sound/SoundPlayerMaker.h"

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

	SoundPlayerMaker& SoundPlayerMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = SoundPlayerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �����̒ǉ��K�w��ݒ�
		m_self.m_targetState = targetState;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<SoundPlayer> SoundPlayerMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.hierarchy.empty())
		{
			return m_user->createComponent<SoundPlayer>(
				m_soundHandle,
				m_isLoop,
				m_startToPlay
				);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<SoundPlayer>(
			m_soundHandle,
			m_isLoop,
			m_startToPlay
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	SoundPlayerMaker& SoundPlayerMaker::soundHandle(unsigned int value)
	{
		m_soundHandle = value;
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

	SoundPlayerMaker& SoundPlayerMaker::soundIdImpl(int value)
	{
		m_soundHandle = DX12GameManager::getSoundHandle(value);
		return *this;
	}
}