#include "TktkDX12BaseComponents/3D/MeshAnimator/MeshAnimatorMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	MeshAnimatorMaker MeshAnimatorMaker::m_self;

	MeshAnimatorMaker& MeshAnimatorMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = MeshAnimatorMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<MeshAnimator> MeshAnimatorMaker::create()
	{
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<MeshAnimator>(m_initMotionHandle, m_initFrame, m_isLoop, m_motionSpeedRate, m_animFramePerSec);
	}

	MeshAnimatorMaker& MeshAnimatorMaker::isLoop(bool value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_isLoop = value;
		return *this;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::motionSpeedRate(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_motionSpeedRate = value;
		return *this;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::initMotionHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initMotionHandle = value;
		return *this;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::initMotionId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initMotionHandle = DX12GameManager::getMotionHandle(value);
		return *this;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::initFrame(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initFrame = value;
		return *this;
	}

	MeshAnimatorMaker& MeshAnimatorMaker::animFramePerSec(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_animFramePerSec = value;
		return *this;
	}
}