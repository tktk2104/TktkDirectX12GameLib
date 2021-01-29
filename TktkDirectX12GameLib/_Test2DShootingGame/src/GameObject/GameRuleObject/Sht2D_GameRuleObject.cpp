#include "Sht2D_GameRuleObject.h"

#include "../../Enums/Enums.h"
#include "Scripts/Sht2D_GameRuleScript.h"

tktk::GameObjectPtr Sht2D_GameRuleObject::create()
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // リザルトシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    // ゲームルールコンポーネント
    gameObject->createComponent<Sht2D_GameRuleScript>();

    return gameObject;
}
