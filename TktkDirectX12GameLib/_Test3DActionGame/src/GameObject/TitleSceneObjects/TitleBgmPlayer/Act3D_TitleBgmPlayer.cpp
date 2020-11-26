#include "Act3D_TitleBgmPlayer.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_TitleBgmPlayer::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // タイトルシーンでのみ生存するオブジェクトタグ
    gameObject->addGameObjectTag(GameObjectTag::TitleSceneObject);

    // タイトルBGMを再生するコンポーネント
    tktk::SoundPlayerMaker::makeStart(gameObject)
        .soundId(SoundId::TitleBGM)
        .startToPlay(true)
        .isLoop(true)
        .create();

    return gameObject;
}