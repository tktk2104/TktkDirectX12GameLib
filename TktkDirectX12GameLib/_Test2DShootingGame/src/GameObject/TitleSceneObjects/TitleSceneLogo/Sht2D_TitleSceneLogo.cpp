#include "Sht2D_TitleSceneLogo.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Sht2D_TitleSceneLogo::create()
{
  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│このフレームワークでは「GameObject」に複数の「Component」を付けることでゲームを作っていきます。
    │　ゲームオブジェクトの作成は「tktk::DX12Game::createGameObject()」で行えます。
	└────────────────────────────────────────────────────────────────────────────────────────*/

    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│ゲームオブジェクトには複数のタグを設定できます。
    │　設定は「gameObject.addGameObjectTag(GameObjectTag)」で行えます。
    │　今回は「main.cpp」で設定した「タイトルシーンが終わると消えるオブジェクトを表すタグ」を設定しています。
	└────────────────────────────────────────────────────────────────────────────────────────*/

    // タイトルシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::TitleSceneObject);


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│「Transform2DMaker」を使うことで「Transform2D」のコンポーネントを作る事ができます。
    │　「Transform2D」コンポーネントは２次元の座標やスケール、回転を管理するコンポーネントです。
	└────────────────────────────────────────────────────────────────────────────────────────*/

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition((tktk::DX12Game::getDrawGameAreaSize() / 2.0f) - tktkMath::Vector2(0.0f, 256.0f))
        .initScaleRate(tktkMath::Vector2(2.0f, 2.0f))
        .create();


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│「TextDrawer2DMaker」を使うことで「TextDrawer2D」のコンポーネントを作る事ができます。
    │　「TextDrawer2D」コンポーネントは２次元のテキストを描画するコンポーネントです。
	└────────────────────────────────────────────────────────────────────────────────────────*/

    // テキスト描画コンポーネント
    tktk::TextDrawer2DMaker::makeStart(gameObject)
        .fontId(FontId::Basic)
        .centerRate(tktkMath::Vector2(0.5f, 0.5f))
        .initText("Test2DShooting")
        .create();

    return gameObject;
}
