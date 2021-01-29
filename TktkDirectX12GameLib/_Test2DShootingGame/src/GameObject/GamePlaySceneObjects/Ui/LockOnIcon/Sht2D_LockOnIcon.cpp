#include "Sht2D_LockOnIcon.h"

#include "../../../../Enums/Enums.h"

tktk::GameObjectPtr Sht2D_LockOnIcon::create()
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .create();

    // ���b�N�I���A�C�R����`�悷��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::LockOnTarget)
        .create();

    return gameObject;
}
