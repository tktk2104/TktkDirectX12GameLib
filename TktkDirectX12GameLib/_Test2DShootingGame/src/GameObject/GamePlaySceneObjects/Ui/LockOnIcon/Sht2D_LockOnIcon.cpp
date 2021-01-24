#include "Sht2D_LockOnIcon.h"

#include "../../../../Enums/Enums.h"

tktk::GameObjectPtr Sht2D_LockOnIcon::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .create();

    // ���b�N�I���A�C�R����`�悷��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(8.0f)
        .spriteMaterialId(SpriteId::LockOnTarget)
        .create();

    return gameObject;
}
