#include "Sht2D_PlayerCollisionReaction.h"

#include "../../../../Enums/Enums.h"
#include "../../Effects/Explosion/Sht2D_Explosion.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"

void Sht2D_PlayerCollisionReaction::update()
{
	if (m_createExplosionIntervalSecTimer < CreateExplosionIntervalTimeSec)
	{
		m_createExplosionIntervalSecTimer += tktk::DX12Game::deltaTime();
	}
}

void Sht2D_PlayerCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// �Փˑ��肪�G�̍U���͈͂�������
	if (other->containGameobjectTag(GameObjectTag::EnemyAttackRange))
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

void Sht2D_PlayerCollisionReaction::onCollisionStay(const tktk::GameObjectPtr& other)
{
	// �Փˑ��肪�G�̍U���͈͂�������
	if (other->containGameobjectTag(GameObjectTag::EnemyAttackRange))
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
