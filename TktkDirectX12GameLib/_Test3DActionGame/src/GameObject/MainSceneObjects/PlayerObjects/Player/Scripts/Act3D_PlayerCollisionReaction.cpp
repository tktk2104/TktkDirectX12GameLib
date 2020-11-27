#include "Act3D_PlayerCollisionReaction.h"

#include "../../../../../Enums/Enums.h"

void Act3D_PlayerCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// �Փˑ��肪�G�̍U���͈͂�������
	if (other->containGameobjectTag(GameObjectTag::EnemyAttackRange))
	{
		// ���g�ɔ�_���[�W���b�Z�[�W�𑗂�i�_���[�W�ʂ͂P�j
		getGameObject()->sendMessage(EventMessageType::Damage, 1);
	}
}
