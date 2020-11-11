#include "TktkDX12BaseComponents/3D/MeshAnimator/MotionChangerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	MotionChangerMaker MotionChangerMaker::m_self;

	MotionChangerMaker& MotionChangerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = MotionChangerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<MotionChanger> MotionChangerMaker::create()
	{
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<MotionChanger>(m_initMotionHandle, m_isLoop, m_motionSpeedRate, m_lerpTimeSec);
	}

	MotionChangerMaker& MotionChangerMaker::isLoop(bool value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_isLoop = value;
		return *this;
	}

	MotionChangerMaker& MotionChangerMaker::motionSpeedRate(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_motionSpeedRate = value;
		return *this;
	}

	MotionChangerMaker& MotionChangerMaker::initMotionHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initMotionHandle = value;
		return *this;
	}

	MotionChangerMaker& MotionChangerMaker::initMotionId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initMotionHandle = DX12GameManager::getMotionHandle(value);
		return *this;
	}

	MotionChangerMaker& MotionChangerMaker::lerpTimeSec(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_lerpTimeSec = value;
		return *this;
	}
}