#include "Sht2D_PlayerMissileCounterScript.h"

#include "../../../../../Enums/Enums.h"

namespace
{
    tktk::GameObjectPtr createMissileIcon(const tktkMath::Vector2& position)
    {
        // �Q�[���I�u�W�F�N�g�����
        tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

        // �񎟌����W�Ǘ��R���|�[�l���g
        tktk::Transform2DMaker::makeStart(gameObject)
            .initPosition(position)
            .create();

        // �X�v���C�g�`��R���|�[�l���g
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::MissileCounterIcon)
            .create();

        return gameObject;
    }
}

void Sht2D_PlayerMissileCounterScript::start()
{
    // �v���C���[�I�u�W�F�N�g���擾����
    tktk::GameObjectPtr playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

    if (playerObject.expired())
    {
        throw std::runtime_error("Sht2D_PlayerMissileCounterScript not found PlayerObject");
    }

    // �v���C���[�I�u�W�F�N�g����c�e���R���|�[�l���g���擾����
    m_playerBulletCount = playerObject->getComponent<Sht2D_PlayerBulletCount>();

    if (m_playerBulletCount.expired())
    {
        throw std::runtime_error("Sht2D_PlayerMissileCounterScript not found Sht2D_PlayerBulletCount");
    }

    // �v���C���[�~�T�C���̎c�e�A�C�R���I�u�W�F�N�g�z��̃��������~�T�C���ő吔�������m�ۂ���
    m_missileIconObjectArray.reserve(m_playerBulletCount->getMaxMissileCount());

    // �v���C���[�~�T�C���ő吔���������[�v����
    for (int i = 0; i < m_playerBulletCount->getMaxMissileCount(); i++)
    {
        // �~�T�C���̎c�e�A�C�R���I�u�W�F�N�g�����
        tktk::GameObjectPtr createdIcon = createMissileIcon(tktkMath::Vector2(MissileIconXInterval * i, 0.0f));

        // ������~�T�C���̎c�e�A�C�R������\���ɂ����ׂ��A�C�R����������A�N�e�B�u�t���O��܂�
        if (i >= m_playerBulletCount->getCurMissileCount()) createdIcon->setActive(false);

        // ���g�̃I�u�W�F�N�g�̎q�v�f�ɍ�����I�u�W�F�N�g��ǉ�����
        getGameObject()->addChild(createdIcon);

        // �v���C���[�~�T�C���̎c�e�A�C�R���I�u�W�F�N�g�z��ɍ�����I�u�W�F�N�g��ǉ�����
        m_missileIconObjectArray.push_back(createdIcon);
    }
}

void Sht2D_PlayerMissileCounterScript::update()
{
    // �v���C���[�̎c�e���R���|�[�l���g�����݂��Ȃ�������֐����I����
    if (m_playerBulletCount.expired()) return;

    // �v���C���[�~�T�C���ő吔���������[�v����
    for (int i = 0; i < m_playerBulletCount->getMaxMissileCount(); i++)
    {
        // ���ꂼ��̎c�e�A�C�R���̃A�N�e�B�u�t���O�����݂̃~�T�C���c�e�����g���ĕύX����
        m_missileIconObjectArray.at(i)->setActive(i < m_playerBulletCount->getCurMissileCount());
    }
}
