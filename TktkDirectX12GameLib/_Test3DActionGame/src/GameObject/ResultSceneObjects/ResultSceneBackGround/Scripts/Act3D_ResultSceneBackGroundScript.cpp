#include "Act3D_ResultSceneBackGroundScript.h"

#include "../../../../Enums/Enums.h"

#include "../../../MainSceneObjects/GameRule/Scripts/Act3D_GameRuleScripts.h"

void Act3D_ResultSceneBackGroundScript::start()
{
	auto gameRuleObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::GameRule);

	if (gameRuleObject->getComponent<Act3D_GameRuleScripts>()->isGameOver())
	{
		tktk::SpriteDrawerMaker::makeStart(getGameObject())
			.drawPriority(8)
			.spriteMaterialId(SpriteId::GameOverSceneBackGround)
			.create();
	}
	else
	{
		tktk::SpriteDrawerMaker::makeStart(getGameObject())
			.drawPriority(8)
			.spriteMaterialId(SpriteId::GameClearSceneBackGround)
			.create();
	}
}
