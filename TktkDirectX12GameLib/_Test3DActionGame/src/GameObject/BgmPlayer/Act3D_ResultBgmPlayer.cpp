#include "Act3D_ResultBgmPlayer.h"

#include "../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_ResultBgmPlayer::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���U���g�V�[�����I���Ǝ��ł���I�u�W�F�N�g�ɕt����^�O
    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    // ���U���gBGM���Đ�����R���|�[�l���g
    tktk::SoundPlayerMaker::makeStart(gameObject)
        .soundId(SoundId::ResultBGM)
        .startToPlay(true)
        .isLoop(true)
        .create();

    return gameObject;
}
