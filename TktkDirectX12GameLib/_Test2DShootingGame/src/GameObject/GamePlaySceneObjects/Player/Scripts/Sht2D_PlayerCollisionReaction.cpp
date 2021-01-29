#include "Sht2D_PlayerCollisionReaction.h"

#include "../../../../Enums/Enums.h"
#include "../../Effects/Explosion/Sht2D_Explosion.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"

void Sht2D_PlayerCollisionReaction::update()
{
	// �����G�t�F�N�g�̏o���Ԋu�^�C�}�[���O���傫�����
	if (m_createExplosionIntervalSecTimer > 0.0f)
	{
		// �J�E���g�_�E������
		m_createExplosionIntervalSecTimer -= tktk::DX12Game::deltaTime();
	}
}

void Sht2D_PlayerCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
    ���w��̃Q�[���I�u�W�F�N�g������̃^�O�������Ă��邩���ʂ��������́ugameObject->containGameobjectTag(tag)�v���g���ĉ������B
    ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

	// �Փˑ��肪�G�̍U���͈͂�������
	if (other->containGameobjectTag(GameObjectTag::EnemyAttackRange))
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
				1,									// �o����
				1.0f								// �����I�u�W�F�N�g��������܂ł̎��ԁi�b�j
			);

			// �����G�t�F�N�g�̏o���Ԋu�^�C�}�[�����Z�b�g
			m_createExplosionIntervalSecTimer = CreateExplosionIntervalTimeSec;
		}


	  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	    ���ugameObject->sendMessage(messageType, anyValue)�v�œ���̃I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗐M���鎖���ł��܂��B
		���@���b�Z�[�W�͑���ꂽ�I�u�W�F�N�g�̑S�R���|�[�l���g�A�S�q�v�f�ɓ`�B����A�uhandleMessage(messageType, anyValue)�v�Ō��m���s���܂��B
		���@�������ɂ͂�����^�̒l���������邱�Ƃ��ł��܂��B�i�����float�^��n���Ă��܂��B�j
		���@���uEventMessageType�v�͎����ō��񋓌^�ł��B
	    ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

		// ���g�ɔ�_���[�W���b�Z�[�W�𑗂�
		getGameObject()->sendMessage(EventMessageType::Damage, other->getComponent<Sht2D_DamagePower>()->getStartHitPower());
	}
}

void Sht2D_PlayerCollisionReaction::onCollisionStay(const tktk::GameObjectPtr& other)
{
	// �Փˑ��肪�G�̍U���͈͂�������
	if (other->containGameobjectTag(GameObjectTag::EnemyAttackRange))
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
				1,									// �o����
				1.0f								// �����I�u�W�F�N�g��������܂ł̎��ԁi�b�j
			);

			// �����G�t�F�N�g�̏o���Ԋu�^�C�}�[�����Z�b�g
			m_createExplosionIntervalSecTimer = CreateExplosionIntervalTimeSec;
		}

		// ���g�ɔ�_���[�W���b�Z�[�W�𑗂�
		getGameObject()->sendMessage(EventMessageType::Damage, other->getComponent<Sht2D_DamagePower>()->getStayHitPowerPerSec() * tktk::DX12Game::deltaTime());
	}
}
