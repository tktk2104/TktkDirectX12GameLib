#include "TktkDX12BaseComponents/2D/Effects/SpriteShrinkEffect/Particle/SpriteShrinkEffectParticle.h"

#include <stdexcept>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"
#include "TktkDX12BaseComponents/2D/Transform2D/Transform2D.h"

namespace tktk
{
	SpriteShrinkEffectParticle::SpriteShrinkEffectParticle(float moveSpeed, float lifeTimeSec)
		: m_moveSpeedPerSec(moveSpeed)
		, m_lifeSecTimer(lifeTimeSec)
	{
	}

	void SpriteShrinkEffectParticle::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteShrinkEffectParticle not found Transform2D");
		}
	}

	void SpriteShrinkEffectParticle::update()
	{
		// �������Ԃ��؂ꂽ��
		if (m_lifeSecTimer <= 0.0f)
		{
			// ���g�̃I�u�W�F�N�g���E��
			getGameObject()->destroy();
			return;
		}

		// �O���Ɉړ�����
		m_transform->addWorldPosition(m_transform->calculateLocalUp() * m_moveSpeedPerSec * DX12GameManager::deltaTime());

		// �������ԃ^�C�}�[���X�V����
		m_lifeSecTimer -= DX12GameManager::deltaTime();
	}
}