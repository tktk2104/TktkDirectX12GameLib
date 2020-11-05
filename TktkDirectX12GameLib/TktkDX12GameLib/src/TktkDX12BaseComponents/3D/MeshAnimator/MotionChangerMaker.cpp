#include "TktkDX12BaseComponents/3D/MeshAnimator/MotionChangerMaker.h"

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

	MotionChangerMaker& MotionChangerMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = MotionChangerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �����̒ǉ��K�w��ݒ�
		m_self.m_targetState = targetState;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<MotionChanger> MotionChangerMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.hierarchy.empty())
		{
			// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
			return m_user->createComponent<MotionChanger>(m_initMotionHandle, m_isLoop, m_lerpTimeSec);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<MotionChanger>(m_initMotionHandle, m_isLoop, m_lerpTimeSec);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	MotionChangerMaker& MotionChangerMaker::isLoop(bool value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_isLoop = value;
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