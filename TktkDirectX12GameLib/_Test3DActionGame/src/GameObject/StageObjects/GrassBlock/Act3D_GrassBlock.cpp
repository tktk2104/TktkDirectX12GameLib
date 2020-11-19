#include "Act3D_GrassBlock.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_GrassBlock::create(const tktkMath::Vector3& position)
{
    // �Q�[���I�u�W�F�N�g���쐬
    auto gameObject = tktk::DX12Game::createGameObject();

    // �R�������W�R���|�[�l���g
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initScaleRate(2.0f)
        .create();

    // ���b�V���`��R���|�[�l���g
    tktk::MeshDrawerMaker::makeStart(gameObject)
        .meshId(BasicMeshId::GrassBlock)
        .baseScale(1.0f)
        .create();

    // OBB�Փ˔���R���|�[�l���g
    tktk::BoxColliderMaker::makeStart(gameObject)
        .boxSize({ 1.0f, 1.0f, 1.0f })
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
