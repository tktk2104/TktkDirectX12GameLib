#include "Sht2D_EnemyNormalBulletCollisionReaction.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_EnemyNormalBulletCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// �Փˑ��肪�v���C���[��������
	if (other->containGameobjectTag(GameObjectTag::Player))
	{
		// ���g�̏����҂��E��
		getGameObject()->destroy();
	}
}