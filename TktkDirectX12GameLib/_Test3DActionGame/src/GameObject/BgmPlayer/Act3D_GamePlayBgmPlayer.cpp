#include "Act3D_GamePlayBgmPlayer.h"

#include "../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_GamePlayBgmPlayer::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // メインシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::MainSceneObject);

    // ゲームプレイBGMを再生するコンポーネント
    tktk::SoundPlayerMaker::makeStart(gameObject)
        .soundId(SoundId::GamePlayBGM)
        .startToPlay(true)
        .isLoop(true)
        .create();

    return gameObject;
}