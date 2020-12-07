#include "Act3D_ResultSceneChanger.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_ResultSceneChangerScript.h"

tktk::GameObjectPtr Act3D_ResultSceneChanger::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ウィンドウサイズを取得
    const auto& drawGameAreaSize = tktk::DX12Game::getDrawGameAreaSize();

    // 座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(drawGameAreaSize / 2.0f)
        .initScaleRate({ drawGameAreaSize.x / 4.0f, drawGameAreaSize.y / 4.0f })
        .create();

    // ゲーム終了キー入力音
    tktk::SoundPlayerMaker::makeStart(gameObject)
        .soundId(SoundId::Confirm)
        .startToPlay(false)
        .isLoop(false)
        .create();

    // リザルトシーンから遷移する処理を行うコンポーネント
    gameObject->createComponent<Act3D_ResultSceneChangerScript>();

    return gameObject;
}
