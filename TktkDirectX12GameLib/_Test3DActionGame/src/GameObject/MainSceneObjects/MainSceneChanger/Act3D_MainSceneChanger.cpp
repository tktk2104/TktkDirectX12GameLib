#include "Act3D_MainSceneChanger.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_MainSceneChangerScript.h"

tktk::GameObjectPtr Act3D_MainSceneChanger::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �E�B���h�E�T�C�Y���擾
    const auto& drawGameAreaSize = tktk::DX12Game::getDrawGameAreaSize();

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(drawGameAreaSize / 2.0f)
        .initScaleRate({ drawGameAreaSize.x / 4.0f, drawGameAreaSize.y / 4.0f })
        .create();

    // �t�F�[�h�p�X�v���C�g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(10)
        .spriteMaterialId(SpriteId::Black4x4)
        .blendRate({ 1.0f, 0.0f })
        .create();

    // ���C���V�[������J�ڂ����鏈�����s���R���|�[�l���g
    gameObject->createComponent<Act3D_MainSceneChangerScript>();

    return gameObject;
}