#include "Act3D_TitleSceneChanger.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_TitleSceneChangerScript.h"

tktk::GameObjectPtr Act3D_TitleSceneChanger::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �E�B���h�E�T�C�Y���擾
    const auto& drawGameAreaSize = tktk::DX12Game::getDrawGameAreaSize();

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(drawGameAreaSize / 2.0f)
        .initScaleRate({ drawGameAreaSize.x / 4.0f, drawGameAreaSize.y / 4.0f })
        .create();

    // �Q�[���J�n�L�[���͉�
    tktk::SoundPlayerMaker::makeStart(gameObject)
        .soundId(SoundId::Confirm)
        .startToPlay(false)
        .isLoop(false)
        .create();

    // �^�C�g���V�[������J�ڂ��鏈�����s���R���|�[�l���g
    gameObject->createComponent<Act3D_TitleSceneChangerScript>();

    return gameObject;
}
