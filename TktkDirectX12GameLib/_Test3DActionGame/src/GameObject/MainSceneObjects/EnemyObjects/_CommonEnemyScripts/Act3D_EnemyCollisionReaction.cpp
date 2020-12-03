#include "Act3D_EnemyCollisionReaction.h"

#include "../../../../Enums/Enums.h"

void Act3D_EnemyCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// �Փˑ��肪�v���C���[�̍U�����肾������
	if (other->containGameobjectTag(GameObjectTag::PlayerAttackRange))
	{
		// ���g�ɔ�_���[�W���b�Z�[�W�𑗂�i�_���[�W�͂P�j
  		getGameObject()->sendMessage(EventMessageType::Damage, 1);
	}
}
