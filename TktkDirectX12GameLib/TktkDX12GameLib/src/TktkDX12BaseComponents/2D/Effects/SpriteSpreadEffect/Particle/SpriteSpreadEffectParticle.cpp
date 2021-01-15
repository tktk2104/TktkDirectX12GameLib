#include "TktkDX12BaseComponents/2D/Effects/SpriteSpreadEffect/Particle/SpriteSpreadEffectParticle.h"

#include <stdexcept>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"
#include "TktkDX12BaseComponents/2D/Transform2D/Transform2D.h"

namespace tktk
{
	SpriteSpreadEffectParticle::SpriteSpreadEffectParticle(float moveSpeed, float lifeTimeSec)
		: m_moveSpeedPerSec(moveSpeed)
		, m_lifeSecTimer(lifeTimeSec)
	{
	}

	void SpriteSpreadEffectParticle::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteSpreadEffectParticle not found Transform2D");
		}
	}

	void SpriteSpreadEffectParticle::update()
	{
		// �������Ԃ��؂ꂽ��
		if (m_lifeSecTimer <= 0.0f)
		{
			// ���g�̃I�u�W�F�N�g���E��
			getGameObject()->destroy();
			return;
		}

		// ����Ɉړ�����
		m_transform->addWorldPosition(m_transform->calculateWorldUp() * m_moveSpeedPerSec * DX12GameManager::deltaTime());

		// �������ԃ^�C�}�[���X�V����
		m_lifeSecTimer -= DX12GameManager::deltaTime();
	}
}