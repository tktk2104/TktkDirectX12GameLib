#include "Act3D_SkyBox.h"

#include "../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_SkyBox::create()
{
    // �Q�[���I�u�W�F�N�g���쐬
    auto gameObject = tktk::DX12Game::createGameObject();

    // �R�������W�R���|�[�l���g
    tktk::Transform3DMaker::makeStart(gameObject)
        .initScaleRate(1.0f)
        .traceType(tktk::TraceParentType::tracePos)
        .create();

    // ���b�V���`��R���|�[�l���g
    tktk::MeshDrawerMaker::makeStart(gameObject)
        .meshId(BasicMeshId::SkyBox)
        .baseScale(100.0f)
        .create();

    return gameObject;
}