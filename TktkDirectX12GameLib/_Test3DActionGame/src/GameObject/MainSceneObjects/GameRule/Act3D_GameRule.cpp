#include "Act3D_GameRule.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_GameRuleScripts.h"

tktk::GameObjectPtr Act3D_GameRule::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // リザルトシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    // ゲームルールオブジェクトタグ
    gameObject->addGameObjectTag(GameObjectTag::GameRule);

    // ゲームルールを管理するコンポーネント
    gameObject->createComponent<Act3D_GameRuleScripts>();

    return gameObject;
}
