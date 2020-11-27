#include "Act3D_ResultSceneBackGroundScript.h"

#include "../../../../Enums/Enums.h"

#include "../../../MainSceneObjects/GameRule/Scripts/Act3D_GameRuleScripts.h"

void Act3D_ResultSceneBackGroundScript::start()
{
	// �Q�[�����[���I�u�W�F�N�g���擾����
	auto gameRuleObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::GameRule);

	// �Q�[���I�[�o�[�t���O�������Ă�����
	if (gameRuleObject->getComponent<Act3D_GameRuleScripts>()->isGameOver())
	{
		// �Q�[���I�[�o�[�̕\�����s���R���|�[�l���g�����
		tktk::SpriteDrawerMaker::makeStart(getGameObject())
			.drawPriority(8)
			.spriteMaterialId(SpriteId::GameOverSceneBackGround)
			.create();
	}
	else
	{
		// �Q�[���N���A�̕\�����s���R���|�[�l���g�����
		tktk::SpriteDrawerMaker::makeStart(getGameObject())
			.drawPriority(8)
			.spriteMaterialId(SpriteId::GameClearSceneBackGround)
			.create();
	}
}
