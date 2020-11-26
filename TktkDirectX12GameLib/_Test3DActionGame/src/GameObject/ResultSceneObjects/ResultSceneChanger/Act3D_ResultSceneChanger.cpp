#include "Act3D_ResultSceneChanger.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_ResultSceneChangerScript.h"

tktk::GameObjectPtr Act3D_ResultSceneChanger::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �E�B���h�E�T�C�Y���擾
    const auto& windowSize = tktk::DX12Game::getWindowSize();

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(windowSize / 2.0f)
        .initScaleRate({ windowSize.x / 4.0f, windowSize.y / 4.0f })
        .create();

    // �Q�[���I���L�[���͉�
    tktk::SoundPlayerMaker::makeStart(gameObject)
        .soundId(SoundId::Confirm)
        .startToPlay(false)
        .isLoop(false)
        .create();

    gameObject->createComponent<Act3D_ResultSceneChangerScript>();

    return gameObject;
}
