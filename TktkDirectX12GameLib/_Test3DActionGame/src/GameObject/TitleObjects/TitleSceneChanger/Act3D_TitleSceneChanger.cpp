#include "Act3D_TitleSceneChanger.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_TitleSceneChangerScript.h"

tktk::GameObjectPtr Act3D_TitleSceneChanger::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �E�B���h�E�T�C�Y���擾
    const auto& windowSize = tktk::DX12Game::getWindowSize();

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(windowSize / 2.0f)
        .initScaleRate({ windowSize.x / 4.0f, windowSize.y / 4.0f })
        .create();

    // �Q�[���J�n�L�[���͉�
    tktk::SoundPlayerMaker::makeStart(gameObject)
        .soundId(SoundId::Confirm)
        .startToPlay(false)
        .isLoop(false)
        .create();

    gameObject->createComponent<Act3D_TitleSceneChangerScript>();

    return gameObject;
}
