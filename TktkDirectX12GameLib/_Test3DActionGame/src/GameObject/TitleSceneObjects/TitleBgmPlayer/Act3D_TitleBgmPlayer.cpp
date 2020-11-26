#include "Act3D_TitleBgmPlayer.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_TitleBgmPlayer::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �^�C�g���V�[���ł̂ݐ�������I�u�W�F�N�g�^�O
    gameObject->addGameObjectTag(GameObjectTag::TitleSceneObject);

    // �^�C�g��BGM���Đ�����R���|�[�l���g
    tktk::SoundPlayerMaker::makeStart(gameObject)
        .soundId(SoundId::TitleBGM)
        .startToPlay(true)
        .isLoop(true)
        .create();

    return gameObject;
}