#include "Sht2D_PlayerNormalBulletCollisionReaction.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_PlayerNormalBulletCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// �Փˑ��肪�G��������
	if (other->containGameobjectTag(GameObjectTag::Enemy))
	{
		// ���g�̏����҂��E��
		getGameObject()->destroy();
	}
}