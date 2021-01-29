#include "Sht2D_ResultSceneMenu.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Sht2D_ResultSceneMenuScript.h"

tktk::GameObjectPtr Sht2D_ResultSceneMenu::create()
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // リザルトシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition((tktk::DX12Game::getDrawGameAreaSize() / 2.0f) + tktkMath::Vector2(0.0f, 128.0f))
        .create();

    // タイトルメニュースクリプト
    gameObject->createComponent<Sht2D_ResultSceneMenuScript>();

    return gameObject;
}
