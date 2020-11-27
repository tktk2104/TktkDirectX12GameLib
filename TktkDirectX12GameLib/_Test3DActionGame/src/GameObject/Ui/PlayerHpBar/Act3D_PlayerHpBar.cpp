#include "Act3D_PlayerHpBar.h"

#include "../../../Enums/Enums.h"

#include "Scripts/Act3D_PlayerHpBarContentScript.h"

inline tktk::GameObjectPtr createPlayerHpBarContent()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition({ 8.0f, 0.0f })
        .create();

    // �L�k����Hp�o�[��`�悷��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(7.0f)
        .spriteMaterialId(SpriteId::PlayerHpBar)
        .centerRate({ 0.0f, 0.5f })
        .create();

    // Hp�o�[��L�k������R���|�[�l���g
    gameObject->createComponent<Act3D_PlayerHpBarContentScript>();

    return gameObject;
}

inline tktk::GameObjectPtr createPlayerHpBarBackGround()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .create();

    // Hp�o�[�w�i��`�悷��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(6.0f)
        .spriteMaterialId(SpriteId::HpBarBackGround)
        .centerRate({ 0.0f, 0.5f })
        .create();

    return gameObject;
}

inline tktk::GameObjectPtr createPlayerHpBarGuide()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition({ 16.0f, -32.0f })
        .create();

    // Hp�o�[�̃K�C�h��`�悷��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(9.0f)
        .spriteMaterialId(SpriteId::PlayerHpBarGuide)
        .create();

    return gameObject;
}

tktk::GameObjectPtr Act3D_PlayerHpBar::create(const tktkMath::Vector2& pos)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���C���V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::MainSceneObject);

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
    gameObject->addChild(createPlayerHpBarBackGround());
    gameObject->addChild(createPlayerHpBarContent());
    gameObject->addChild(createPlayerHpBarGuide());

    return gameObject;
}
