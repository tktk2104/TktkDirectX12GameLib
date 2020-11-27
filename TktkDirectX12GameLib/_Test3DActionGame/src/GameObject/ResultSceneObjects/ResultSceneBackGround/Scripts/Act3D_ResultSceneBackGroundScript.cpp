#include "Act3D_ResultSceneBackGroundScript.h"

#include "../../../../Enums/Enums.h"

#include "../../../MainSceneObjects/GameRule/Scripts/Act3D_GameRuleScripts.h"

void Act3D_ResultSceneBackGroundScript::start()
{
	// ゲームルールオブジェクトを取得する
	auto gameRuleObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::GameRule);

	// ゲームオーバーフラグが立っていたら
	if (gameRuleObject->getComponent<Act3D_GameRuleScripts>()->isGameOver())
	{
		// ゲームオーバーの表示を行うコンポーネントを作る
		tktk::SpriteDrawerMaker::makeStart(getGameObject())
			.drawPriority(8)
			.spriteMaterialId(SpriteId::GameOverSceneBackGround)
			.create();
	}
	else
	{
		// ゲームクリアの表示を行うコンポーネントを作る
		tktk::SpriteDrawerMaker::makeStart(getGameObject())
			.drawPriority(8)
			.spriteMaterialId(SpriteId::GameClearSceneBackGround)
			.create();
	}
}
