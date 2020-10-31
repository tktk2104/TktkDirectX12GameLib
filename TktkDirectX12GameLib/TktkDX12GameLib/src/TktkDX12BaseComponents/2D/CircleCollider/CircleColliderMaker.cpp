#include "TktkDX12BaseComponents/2D/CircleCollider/CircleColliderMaker.h"

namespace tktk
{
	CircleColliderMaker CircleColliderMaker::m_self;

	CircleColliderMaker & CircleColliderMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = CircleColliderMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<CircleCollider> CircleColliderMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.empty())
		{
			// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
			return m_user->createComponent<CircleCollider>(
				m_collisionGroupType,
				m_radius,
				m_localPosition,
				m_extrudedRate
				);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<CircleCollider>(
			m_collisionGroupType,
			m_radius,
			m_localPosition,
			m_extrudedRate
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	CircleColliderMaker & CircleColliderMaker::radius(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_radius = value;
		return *this;
	}

	CircleColliderMaker & CircleColliderMaker::localPosition(const tktkMath::Vector2 & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_localPosition = value;
		return *this;
	}

	CircleColliderMaker& CircleColliderMaker::extrudedRate(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_extrudedRate = value;
		return *this;
	}

	CircleColliderMaker& CircleColliderMaker::collisionGroupTypeImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_collisionGroupType = value;
		return *this;
	}
}