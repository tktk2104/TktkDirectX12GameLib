#include "Sht2D_StageSelectSceneMenu.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Sht2D_StageSelectSceneMenuScript.h"

tktk::GameObjectPtr Sht2D_StageSelectSceneMenu::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ステージセレクトシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::StageSelectSceneObject);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition((tktk::DX12Game::getDrawGameAreaSize() / 2.0f))
        .create();

    // ステージセレクトメニュースクリプト
    gameObject->createComponent<Sht2D_StageSelectSceneMenuScript>();

    return gameObject;
}
