#include "Act3D_ResultSceneChanger.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_ResultSceneChangerScript.h"

tktk::GameObjectPtr Act3D_ResultSceneChanger::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �E�B���h�E�T�C�Y���擾
    const auto& drawGameAreaSize = tktk::DX12Game::getDrawGameAreaSize();

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(drawGameAreaSize / 2.0f)
        .initScaleRate({ drawGameAreaSize.x / 4.0f, drawGameAreaSize.y / 4.0f })
        .create();

    // �Q�[���I���L�[���͉�
    tktk::SoundPlayerMaker::makeStart(gameObject)
        .soundId(SoundId::Confirm)
        .startToPlay(false)
        .isLoop(false)
        .create();

    // ���U���g�V�[������J�ڂ��鏈�����s���R���|�[�l���g
    gameObject->createComponent<Act3D_ResultSceneChangerScript>();

    return gameObject;
}
