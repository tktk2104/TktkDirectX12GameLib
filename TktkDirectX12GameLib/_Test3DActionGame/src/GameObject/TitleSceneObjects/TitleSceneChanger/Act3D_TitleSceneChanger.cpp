#include "Act3D_TitleSceneChanger.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_TitleSceneChangerScript.h"

tktk::GameObjectPtr Act3D_TitleSceneChanger::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ウィンドウサイズを取得
    const auto& drawGameAreaSize = tktk::DX12Game::getDrawGameAreaSize();

    // 座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(drawGameAreaSize / 2.0f)
        .initScaleRate({ drawGameAreaSize.x / 4.0f, drawGameAreaSize.y / 4.0f })
        .create();

    // ゲーム開始キー入力音
    tktk::SoundPlayerMaker::makeStart(gameObject)
        .soundId(SoundId::Confirm)
        .startToPlay(false)
        .isLoop(false)
        .create();

    // タイトルシーンから遷移する処理を行うコンポーネント
    gameObject->createComponent<Act3D_TitleSceneChangerScript>();

    return gameObject;
}
