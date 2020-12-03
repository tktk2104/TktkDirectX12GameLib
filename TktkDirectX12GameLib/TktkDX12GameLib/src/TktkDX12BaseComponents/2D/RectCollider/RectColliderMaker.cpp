#include "TktkDX12BaseComponents/2D/RectCollider/RectColliderMaker.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	RectColliderMaker RectColliderMaker::m_self;

	RectColliderMaker & RectColliderMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = RectColliderMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<RectCollider> RectColliderMaker::create()
	{
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<RectCollider>(
			m_collisionGroupType,
			m_rectSize,
			m_localPosition,
			m_isExtrude,
			m_extrudedRate
			);
	}

	RectColliderMaker& RectColliderMaker::collisionGroupType(CollisionGroupTypeCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_collisionGroupType = value;
		return *this;
	}

	RectColliderMaker & RectColliderMaker::rectSize(const tktkMath::Vector2 & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_rectSize = value;
		return *this;
	}

	RectColliderMaker & RectColliderMaker::localPosition(const tktkMath::Vector2 & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_localPosition = value;
		return *this;
	}

	RectColliderMaker& RectColliderMaker::isExtrude(bool value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_isExtrude = value;
		return *this;
	}

	RectColliderMaker& RectColliderMaker::extrudedRate(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_extrudedRate = value;
		return *this;
	}
}