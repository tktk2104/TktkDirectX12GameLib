#include "TktkDX12BaseComponents/2D/CircleCollider/CircleColliderMaker.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

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
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<CircleCollider>(
			m_collisionGroupType,
			m_radius,
			m_localPosition,
			m_isExtrude,
			m_extrudedRate
			);
	}

	CircleColliderMaker& CircleColliderMaker::collisionGroupType(CollisionGroupTypeCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_collisionGroupType = value;
		return *this;
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

	CircleColliderMaker& CircleColliderMaker::isExtrude(bool value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_isExtrude = value;
		return *this;
	}

	CircleColliderMaker& CircleColliderMaker::extrudedRate(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_extrudedRate = value;
		return *this;
	}
}