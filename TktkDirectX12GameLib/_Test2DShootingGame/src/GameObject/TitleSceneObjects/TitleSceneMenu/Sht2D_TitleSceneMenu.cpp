#include "Sht2D_TitleSceneMenu.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Sht2D_TitleSceneMenuScript.h"

tktk::GameObjectPtr Sht2D_TitleSceneMenu::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // タイトルシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::TitleSceneObject);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition((tktk::DX12Game::getDrawGameAreaSize() / 2.0f) + tktkMath::Vector2(0.0f, 128.0f))
        .create();

    // タイトルメニュースクリプト
    gameObject->createComponent<Sht2D_TitleSceneMenuScript>();

    return gameObject;
}
