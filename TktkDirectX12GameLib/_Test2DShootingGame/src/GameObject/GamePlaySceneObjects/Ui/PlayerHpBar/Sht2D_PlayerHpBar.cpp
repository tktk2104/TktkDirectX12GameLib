#include "Sht2D_PlayerHpBar.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_PlayerHpBarScript.h"

namespace
{
    inline tktk::GameObjectPtr createHpBarContent()
    {
        auto gameObject = tktk::DX12Game::createGameObject();

        // ���W�Ǘ��R���|�[�l���g
        tktk::Transform2DMaker::makeStart(gameObject)
            .initPosition({ 8.0f, 0.0f })
            .create();

        // �L�k����Hp�o�[��`�悷��R���|�[�l���g
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::HpBarContent)
            .centerRate({ 0.0f, 0.5f })
            .blendRate(tktkMath::Color_v::blue)
            .create();

        // Hp�o�[��L�k������R���|�[�l���g
        gameObject->createComponent<Sht2D_PlayerHpBarScript>();

        return gameObject;
    }

    inline tktk::GameObjectPtr createHpBarBackGround()
    {
        auto gameObject = tktk::DX12Game::createGameObject();

        // ���W�Ǘ��R���|�[�l���g
        tktk::Transform2DMaker::makeStart(gameObject)
            .create();

        // Hp�o�[�w�i��`�悷��R���|�[�l���g
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::HpBarBackGround)
            .centerRate({ 0.0f, 0.5f })
            .create();

        return gameObject;
    }

    inline tktk::GameObjectPtr createHpBarGuide()
    {
        auto gameObject = tktk::DX12Game::createGameObject();

        // ���W�Ǘ��R���|�[�l���g
        tktk::Transform2DMaker::makeStart(gameObject)
            .initPosition({ -128.0f, 0.0f })
            .initScaleRate({ 0.4f })
            .create();

        tktk::TextDrawer2DMaker::makeStart(gameObject)
            .fontId(FontId::Basic)
            .initText("PlayerHp")
            .centerRate({ 0.0f, 0.5f })
            .create();

        return gameObject;
    }
}

tktk::GameObjectPtr Sht2D_PlayerHpBar::create(const tktkMath::Vector2& pos)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(pos)
        .create();

    // Hp�o�[�̊O�g��`�悷��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(8.0f)
        .spriteMaterialId(SpriteId::HpBarFrame)
        .centerRate({ 0.0f, 0.5f })
        .create();

    // Ui���`������p�[�c�����g�̎q�v�f�ɒǉ�����
    gameObject->addChild(createHpBarBackGround());
    gameObject->addChild(createHpBarContent());
    gameObject->addChild(createHpBarGuide());

    return gameObject;
}
