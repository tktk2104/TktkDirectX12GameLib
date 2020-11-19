#include "Act3D_BaseGround.h"

#include "../../../Enums/Enums.h"


constexpr int BaseGroundSize{ 10 };

tktk::GameObjectPtr Act3D_BaseGround::create()
{
    // �Q�[���I�u�W�F�N�g���쐬
    auto gameObject = tktk::DX12Game::createGameObject();

    // �R�������W�R���|�[�l���g
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition({ 0.0f, 0.0f, 0.0f })
        .create();

    for (int i = -BaseGroundSize; i <= BaseGroundSize; i++)
    {
        for (int j = -BaseGroundSize; j <= BaseGroundSize; j++)
        {
            tktk::MeshDrawerMaker::makeStart(gameObject)
                .meshId(BasicMeshId::GrassBlock)
                .basePosition({ (3.0f * i), -1.5f, (3.0f * j) })
                .baseScale(3.0f)
                .create();
        }
    }

    // OBB�Փ˔���R���|�[�l���g
    tktk::BoxColliderMaker::makeStart(gameObject)
        .boxSize({ 63.0f, 10.0f, 63.0f })
        .localPosition({ 0.0f, -5.0f, 0.0f })
        .collisionGroupType(CollisionGroup::Stage)
        .isExtrude(true)
        .extrudedRate(0.0f)
        .create();

// �Փ˔���͈͕`��R���|�[�l���g
#ifdef _DEBUG
    tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::white)
        .create();
#endif // _DEBUG

    return gameObject;
}
