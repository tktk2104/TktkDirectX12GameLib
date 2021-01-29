#include "Sht2D_EnemyCollisionReaction.h"

#include "../../../../../Enums/Enums.h"
#include "../../../Effects/Explosion/Sht2D_Explosion.h"
#include "../../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"

void Sht2D_EnemyCollisionReaction::update()
{
	// �����G�t�F�N�g�̏o���Ԋu�^�C�}�[���O���傫�����
	if (m_createExplosionIntervalSecTimer > 0.0f)
	{
		// �J�E���g�_�E������
		m_createExplosionIntervalSecTimer -= tktk::DX12Game::deltaTime();
	}
}

void Sht2D_EnemyCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// �Փˑ��肪�v���C���[�̍U���͈͂�������
	if (other->containGameobjectTag(GameObjectTag::PlayerAttackRange))
	{
		// �����G�t�F�N�g�̏o���Ԋu�^�C�}�[�J�E���g���I����Ă�����
		if (m_createExplosionIntervalSecTimer <= 0.0f)
		{
			tktk::ComponentPtr<tktk::Transform2D> otherTransform = other->getComponent<tktk::Transform2D>();

			// �����𐶐�����
			Sht2D_Explosion::create(
				otherTransform->getWorldPosition(),	// �������W
				tktkMath::Vector2_v::zero,			// �������W�̃Y����
				0.0f,								// �o���Ԋu
				1U,									// �o����
				1.0f								// �����I�u�W�F�N�g��������܂ł̎��ԁi�b�j
			);

			// �����G�t�F�N�g�̏o���Ԋu�^�C�}�[�����Z�b�g
			m_createExplosionIntervalSecTimer = CreateExplosionIntervalTimeSec;
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
		// �����G�t�F�N�g�̏o���Ԋu�^�C�}�[�J�E���g���I����Ă�����
		if (m_createExplosionIntervalSecTimer <= 0.0f)
		{
			// �Փˑ���̍��W�Ǘ��R���|�[�l���g���擾����
			tktk::ComponentPtr<tktk::Transform2D> otherTransform = other->getComponent<tktk::Transform2D>();

			// �����𐶐�����
			Sht2D_Explosion::create(
				otherTransform->getWorldPosition(),	// �������W
				tktkMath::Vector2_v::zero,			// �������W�̃Y����
				0.0f,								// �o���Ԋu
				1U,									// �o����
				1.0f								// �����I�u�W�F�N�g��������܂ł̎��ԁi�b�j
			);

			// �����G�t�F�N�g�̏o���Ԋu�^�C�}�[�����Z�b�g
			m_createExplosionIntervalSecTimer = CreateExplosionIntervalTimeSec;
		}

		// ���g�ɔ�_���[�W���b�Z�[�W�𑗂�
		getGameObject()->sendMessage(EventMessageType::Damage, other->getComponent<Sht2D_DamagePower>()->getStayHitPowerPerSec() * tktk::DX12Game::deltaTime());
	}
}
