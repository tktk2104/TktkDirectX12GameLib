#include "Act3D_ResultBgmPlayer.h"

#include "../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_ResultBgmPlayer::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // リザルトシーンが終わると自滅するオブジェクトに付けるタグ
    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    // リザルトBGMを再生するコンポーネント
    tktk::SoundPlayerMaker::makeStart(gameObject)
        .soundId(SoundId::ResultBGM)
        .startToPlay(true)
        .isLoop(true)
        .create();

    return gameObject;
}
