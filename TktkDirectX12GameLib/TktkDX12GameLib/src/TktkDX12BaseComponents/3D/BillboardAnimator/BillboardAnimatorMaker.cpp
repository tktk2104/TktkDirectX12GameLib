#include "TktkDX12BaseComponents/3D/BillboardAnimator/BillboardAnimatorMaker.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	BillboardAnimatorMaker BillboardAnimatorMaker::m_self;

	BillboardAnimatorMaker& BillboardAnimatorMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BillboardAnimatorMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<BillboardAnimator> BillboardAnimatorMaker::create()
	{
		return m_user->createComponent<BillboardAnimator>(
			m_initFrame,
			m_isLoop,
			m_animSpeedRate,
			m_animFramePerSec,
			m_totalAnimFrameSize
			);
	}

	BillboardAnimatorMaker& BillboardAnimatorMaker::isLoop(bool value)
	{
		m_isLoop = value;
		return *this;
	}

	BillboardAnimatorMaker& BillboardAnimatorMaker::initFrame(float value)
	{
		m_initFrame = value;
		return *this;
	}

	BillboardAnimatorMaker& BillboardAnimatorMaker::animSpeedRate(float value)
	{
		m_animSpeedRate = value;
		return *this;
	}

	BillboardAnimatorMaker& BillboardAnimatorMaker::animFramePerSec(float value)
	{
		m_animFramePerSec = value;
		return *this;
	}

	BillboardAnimatorMaker& BillboardAnimatorMaker::totalAnimFrameSize(unsigned int value)
	{
		m_totalAnimFrameSize = value;
		return *this;
	}
}