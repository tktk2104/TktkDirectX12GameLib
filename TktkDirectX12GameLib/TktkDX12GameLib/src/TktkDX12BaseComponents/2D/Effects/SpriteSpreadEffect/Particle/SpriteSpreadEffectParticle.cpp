#include "TktkDX12BaseComponents/2D/Effects/SpriteSpreadEffect/Particle/SpriteSpreadEffectParticle.h"

#include <stdexcept>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"
#include "TktkDX12BaseComponents/2D/Transform2D/Transform2D.h"
#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawer.h"

namespace tktk
{
	SpriteSpreadEffectParticle::SpriteSpreadEffectParticle(const ComponentPtr<SpriteDrawer>& targetDrawer, float moveSpeed, const tktkMath::Vector2& scalingSize, const tktkMath::Color& blendRateChangeWidth, float lifeTimeSec)
		: m_spriteDrawer(targetDrawer)
		, m_moveSpeedPerSec(moveSpeed)
		, m_scalingSizePerSec(scalingSize)
		, m_blendRateChangeWidthPerSec(blendRateChangeWidth)
		, m_lifeSecTimer(lifeTimeSec)
	{
	}

	void SpriteSpreadEffectParticle::update()
	{
		// �������Ԃ��؂ꂽ��
		if (m_lifeSecTimer <= 0.0f)
		{
			// ���g�ƃX�v���C�g�R���|�[�l���g���E��
			m_spriteDrawer->destroy();
			destroy();
			return;
		}

		// ����Ɉړ�����
		auto moveVec = tktkMath::Matrix3::createRotation(m_spriteDrawer->getLocalRotationDeg()).calculateUp();
		m_spriteDrawer->addLocalPosition(moveVec * m_moveSpeedPerSec * DX12GameManager::deltaTime());

		// �X�P�[���𑝉�������
		m_spriteDrawer->addLocalScaleRate(m_scalingSizePerSec * DX12GameManager::deltaTime());

		// ���݂̃u�����h���[�g���擾����
		tktkMath::Color curBlendRate = m_spriteDrawer->getBlendRate();

		// ���̃t���[���̃u�����h���[�g���v�Z����i0.0f�`1.0f�̊ԂɎ��߂�j
		curBlendRate = tktkMath::Color::clamp(curBlendRate + m_blendRateChangeWidthPerSec * DX12GameManager::deltaTime());

		// �u�����h���[�g���X�V����
		m_spriteDrawer->setBlendRate(curBlendRate);

		// �������ԃ^�C�}�[���X�V����
		m_lifeSecTimer -= DX12GameManager::deltaTime();
	}
}