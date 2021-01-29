#include "Sht2D_TitleSceneMenu.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Sht2D_TitleSceneMenuScript.h"

tktk::GameObjectPtr Sht2D_TitleSceneMenu::create()
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // タイトルシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::TitleSceneObject);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition((tktk::DX12Game::getDrawGameAreaSize() / 2.0f) + tktkMath::Vector2(0.0f, 128.0f))
        .create();


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│自作のコンポーネントの追加は「gameObject.createComponent<ComponentType>(constructorArgs...)」で行えます。
    │　※自作コンポーネントの作成方法は次で説明します。
	└────────────────────────────────────────────────────────────────────────────────────────*/


  /*┌────────────────────────────────────────────────────────────────────────────────────────
    │下の「Sht2D_TitleSceneMenuScript」をシングルクリック＆F12キーを入力してソースファイルに飛んで下さい。
	└────────────────────────────────────────────────────────────────────────────────────────*/

    // タイトルメニュースクリプト
    gameObject->createComponent<Sht2D_TitleSceneMenuScript>();

    return gameObject;
}
