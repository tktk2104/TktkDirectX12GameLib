#include "Act3D_TitleSceneChanger.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_TitleSceneChangerScript.h"

tktk::GameObjectPtr Act3D_TitleSceneChanger::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ウィンドウサイズを取得
    const auto& windowSize = tktk::DX12Game::getWindowSize();

    // 座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(windowSize / 2.0f)
        .initScaleRate({ windowSize.x / 4.0f, windowSize.y / 4.0f })
        .create();

    // ゲーム開始キー入力音
    tktk::SoundPlayerMaker::makeStart(gameObject)
        .soundId(SoundId::Confirm)
        .startToPlay(false)
        .isLoop(false)
        .create();

    gameObject->createComponent<Act3D_TitleSceneChangerScript>();

    return gameObject;
}
