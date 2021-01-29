#include "Sht2D_Flame.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_FlameScript.h"

tktk::GameObjectPtr Sht2D_Flame::create(const tktkMath::Vector2& position, float rotate)
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotationDeg(rotate)
        .create();

    // �X�v���C�g�`��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Flame)
        .centerRate(tktkMath::Vector2(0.5f, 1.0f))
        .create();

    // ���G�t�F�N�g�̃A�j���[�V�����R���|�[�l���g
    gameObject->createComponent<Sht2D_FlameScript>();

    return gameObject;
}