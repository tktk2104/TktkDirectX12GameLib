#include "TktkDX12BaseComponents/Other/Sound/SoundPlayTimerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	SoundPlayTimerMaker SoundPlayTimerMaker::m_self;

	SoundPlayTimerMaker& SoundPlayTimerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = SoundPlayTimerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<SoundPlayTimer> SoundPlayTimerMaker::create()
	{
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<SoundPlayTimer>(
			m_soundHandle,
			m_firstPlayStartTimeSec,
			m_playIntervalSec,
			m_playCount,
			m_startToPlay
			);
	}

	SoundPlayTimerMaker& SoundPlayTimerMaker::soundHandle(size_t value)
	{
		m_soundHandle = value;
		return *this;
	}

	SoundPlayTimerMaker& SoundPlayTimerMaker::soundId(ResourceIdCarrier value)
	{
		m_soundHandle = DX12GameManager::getSoundHandle(value);
		return *this;
	}

	SoundPlayTimerMaker& SoundPlayTimerMaker::firstPlayStartTimeSec(float value)
	{
		m_firstPlayStartTimeSec = value;
		return *this;
	}

	SoundPlayTimerMaker& SoundPlayTimerMaker::playIntervalSec(float value)
	{
		m_playIntervalSec = value;
		return *this;
	}

	SoundPlayTimerMaker& SoundPlayTimerMaker::playCount(int value)
	{
		m_playCount = value;
		return *this;
	}

	SoundPlayTimerMaker& SoundPlayTimerMaker::startToPlay(bool value)
	{
		m_startToPlay = value;
		return *this;
	}
}