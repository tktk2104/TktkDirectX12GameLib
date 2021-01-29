#include "Sht2D_PlayerHpBar.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_PlayerHpBarScript.h"

namespace
{
    inline tktk::GameObjectPtr createHpBarContent()
    {
        // �Q�[���I�u�W�F�N�g�����
        tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

        // ���W�Ǘ��R���|�[�l���g
        tktk::Transform2DMaker::makeStart(gameObject)
            .initPosition(tktkMath::Vector2(8.0f, 0.0f))
            .create();

        // �L�k����Hp�o�[��`�悷��R���|�[�l���g
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::HpBarContent)
            .centerRate(tktkMath::Vector2(0.0f, 0.5f))
            .blendRate(tktkMath::Color_v::blue)
            .create();

        // Hp�o�[��L�k������R���|�[�l���g
        gameObject->createComponent<Sht2D_PlayerHpBarScript>();

        return gameObject;
    }

    inline tktk::GameObjectPtr createHpBarBackGround()
    {
        // �Q�[���I�u�W�F�N�g�����
        tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

        // ���W�Ǘ��R���|�[�l���g
        tktk::Transform2DMaker::makeStart(gameObject)
            .create();

        // Hp�o�[�w�i��`�悷��R���|�[�l���g
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::HpBarBackGround)
            .centerRate(tktkMath::Vector2(0.0f, 0.5f))
            .create();

        return gameObject;
    }

    inline tktk::GameObjectPtr createHpBarGuide()
    {
        // �Q�[���I�u�W�F�N�g�����
        tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

        // ���W�Ǘ��R���|�[�l���g
        tktk::Transform2DMaker::makeStart(gameObject)
            .initPosition(tktkMath::Vector2(-128.0f, 0.0f))
            .initScaleRate(tktkMath::Vector2(0.4f, 0.4f))
            .create();

        // �g�v���C���[HP�h�̕�����`�悷��R���|�[�l���g
        tktk::TextDrawer2DMaker::makeStart(gameObject)
            .fontId(FontId::Basic)
            .initText("PlayerHp")
            .centerRate(tktkMath::Vector2(0.0f, 0.5f))
            .create();

        return gameObject;
    }
}

tktk::GameObjectPtr Sht2D_PlayerHpBar::create(const tktkMath::Vector2& pos)
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(pos)
        .create();

    // Hp�o�[�̊O�g��`�悷��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::HpBarFrame)
        .centerRate(tktkMath::Vector2(0.0f, 0.5f))
        .create();

    // Ui���`������p�[�c�����g�̎q�v�f�ɒǉ�����
    gameObject->addChild(createHpBarBackGround());
    gameObject->addChild(createHpBarContent());
    gameObject->addChild(createHpBarGuide());

    return gameObject;
}
