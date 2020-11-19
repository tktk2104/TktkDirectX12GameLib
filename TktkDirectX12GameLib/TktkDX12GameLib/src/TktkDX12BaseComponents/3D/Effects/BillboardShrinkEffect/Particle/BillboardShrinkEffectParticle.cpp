#include "TktkDX12BaseComponents/3D/Effects/BillboardShrinkEffect/Particle/BillboardShrinkEffectParticle.h"

#include <stdexcept>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"
#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"

namespace tktk
{
	BillboardShrinkEffectParticle::BillboardShrinkEffectParticle(float moveSpeed, float lifeTimeSec)
		: m_moveSpeedPerSec(moveSpeed)
		, m_lifeSecTimer(lifeTimeSec)
	{
	}

	void BillboardShrinkEffectParticle::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BillboardShrinkEffectParticle not found Transform3D");
		}
	}

	void BillboardShrinkEffectParticle::update()
	{
		// �������Ԃ��؂ꂽ��
		if (m_lifeSecTimer <= 0.0f)
		{
			// ���g�̃I�u�W�F�N�g���E��
			getGameObject()->destroy();
			return;
		}

		// �O���Ɉړ�����
		m_transform->addWorldPosition(m_transform->calculateWorldForwardLH() * m_moveSpeedPerSec * DX12GameManager::deltaTime());

		// �������ԃ^�C�}�[���X�V����
		m_lifeSecTimer -= DX12GameManager::deltaTime();
	}
}