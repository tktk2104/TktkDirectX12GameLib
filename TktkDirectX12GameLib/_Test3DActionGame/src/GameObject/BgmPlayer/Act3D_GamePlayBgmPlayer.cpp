#include "Act3D_GamePlayBgmPlayer.h"

#include "../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_GamePlayBgmPlayer::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���C���V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::MainSceneObject);

    // �Q�[���v���CBGM���Đ�����R���|�[�l���g
    tktk::SoundPlayerMaker::makeStart(gameObject)
        .soundId(SoundId::GamePlayBGM)
        .startToPlay(true)
        .isLoop(true)
        .create();

    return gameObject;
}