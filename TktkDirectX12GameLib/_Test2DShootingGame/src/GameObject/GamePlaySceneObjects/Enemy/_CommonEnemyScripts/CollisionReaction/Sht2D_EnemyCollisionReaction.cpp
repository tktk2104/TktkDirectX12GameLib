#include "Sht2D_EnemyCollisionReaction.h"

#include "../../../../../Enums/Enums.h"
#include "../../../Effects/Explosion/Sht2D_Explosion.h"
#include "../../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"

void Sht2D_EnemyCollisionReaction::update()
{
	if (m_createExplosionIntervalSecTimer < CreateExplosionIntervalTimeSec)
	{
		m_createExplosionIntervalSecTimer += tktk::DX12Game::deltaTime();
	}
}

void Sht2D_EnemyCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// �Փˑ��肪�v���C���[�̍U���͈͂�������
	if (other->containGameobjectTag(GameObjectTag::PlayerAttackRange))
	{
		auto otherTransform = other->getComponent<tktk::Transform2D>();

		if (m_createExplosionIntervalSecTimer >= CreateExplosionIntervalTimeSec)
		{
			// �����𐶐�����
			Sht2D_Explosion::create(
				otherTransform->getWorldPosition(),
				tktkMath::Vector2_v::zero,
				0.0f,
				1U,
				1.0f
			);

			m_createExplosionIntervalSecTimer = 0.0f;
		}

		// ���g�ɔ�_���[�W���b�Z�[�W�𑗂�
		getGameObject()->sendMessage(EventMessageType::Damage, other->getComponent<Sht2D_DamagePower>()->getStartHitPower());
	}
}

void Sht2D_EnemyCollisionReaction::onCollisionStay(const tktk::GameObjectPtr& other)
{
	// �Փˑ��肪�v���C���[�̍U���͈͂�������
	if (other->containGameobjectTag(GameObjectTag::PlayerAttackRange))
	{
		auto otherTransform = other->getComponent<tktk::Transform2D>();

		if (m_createExplosionIntervalSecTimer >= CreateExplosionIntervalTimeSec)
		{
			// �����𐶐�����
			Sht2D_Explosion::create(
				otherTransform->getWorldPosition(),
				tktkMath::Vector2_v::zero,
				0.0f,
				1U,
				1.0f
			);

			m_createExplosionIntervalSecTimer = 0.0f;
		}

		// ���g�ɔ�_���[�W���b�Z�[�W�𑗂�
		getGameObject()->sendMessage(EventMessageType::Damage, other->getComponent<Sht2D_DamagePower>()->getStayHitPowerPerSec() * tktk::DX12Game::deltaTime());
	}
}
