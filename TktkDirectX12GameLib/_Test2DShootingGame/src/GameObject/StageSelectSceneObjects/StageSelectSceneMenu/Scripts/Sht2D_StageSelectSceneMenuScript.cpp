#include "Sht2D_StageSelectSceneMenuScript.h"

#include "../../../../Enums/Enums.h"

namespace
{
    // ���j���[�̗v�f�����֐��i�������W�A�����F�A�\������e�L�X�g�j
    inline tktk::GameObjectPtr createMenuContant(const tktkMath::Vector2& position, const tktkMath::Color& color, const std::string& menuText)
    {
        // �Q�[���I�u�W�F�N�g�����
        tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

        // �񎟌����W�Ǘ��R���|�[�l���g
        tktk::Transform2DMaker::makeStart(gameObject)
            .initPosition(position)
            .create();

        // �e�L�X�g�`��R���|�[�l���g
        tktk::TextDrawer2DMaker::makeStart(gameObject)
            .fontId(FontId::Basic)
            .centerRate(tktkMath::Vector2(0.5f, 0.5f))
            .blendRate(color)
            .initText(menuText)
            .create();

        return gameObject;
    }
}

void Sht2D_StageSelectSceneMenuScript::start()
{
    // ���j���[�̗v�f�����A���̃|�C���^��z��ɕۑ�����
    m_menuContantObjectArray = {
        createMenuContant(tktkMath::Vector2(0.0f,   0.0f), tktkMath::Color_v::red,      "Stage1"),
        createMenuContant(tktkMath::Vector2(0.0f, 128.0f), tktkMath::Color_v::white,    "Stage2"),
        createMenuContant(tktkMath::Vector2(0.0f, 256.0f), tktkMath::Color_v::white,    "Stage3"),
        createMenuContant(tktkMath::Vector2(0.0f, 384.0f), tktkMath::Color_v::white,    "Back")
    };

    // ���j���[�̗v�f�����g�̎q�v�f�ɒǉ�����
    getGameObject()->addChild(m_menuContantObjectArray.at(0U));
    getGameObject()->addChild(m_menuContantObjectArray.at(1U));
    getGameObject()->addChild(m_menuContantObjectArray.at(2U));
    getGameObject()->addChild(m_menuContantObjectArray.at(3U));
}

void Sht2D_StageSelectSceneMenuScript::update()
{
    // ����L�[�������ꂽ��
    if (tktk::DX12Game::isTrigger(CommandId::Decision))
    {
        // ���݂̃��j���[�̏�Ԃŕ���
        switch (m_curMenuState)
        {
        // �g�X�e�[�W�P�h���ڂ��I������Ă�����
        case MenuContantType::Stage1:

            // �X�e�[�W�P�V�[���ֈڍs
            tktk::DX12Game::enableScene(SceneId::GamePlay);
            tktk::DX12Game::enableScene(SceneId::Stage1);
            tktk::DX12Game::disableScene(SceneId::StageSelect);
            break;

        // �g�X�e�[�W�Q�h���ڂ��I������Ă�����
        case MenuContantType::Stage2:

            // �X�e�[�W�Q�V�[���ֈڍs
            tktk::DX12Game::enableScene(SceneId::GamePlay);
            tktk::DX12Game::enableScene(SceneId::Stage2);
            tktk::DX12Game::disableScene(SceneId::StageSelect);
            break;

        // �g�X�e�[�W�R�h���ڂ��I������Ă�����
        case MenuContantType::Stage3:

            // �X�e�[�W�R�V�[���ֈڍs
            tktk::DX12Game::enableScene(SceneId::GamePlay);
            tktk::DX12Game::enableScene(SceneId::Stage3);
            tktk::DX12Game::disableScene(SceneId::StageSelect);
            break;

        // �g�߂�h���ڂ��I������Ă�����
        case MenuContantType::Back:

            // �^�C�g���V�[���ֈڍs
            tktk::DX12Game::enableScene(SceneId::Title);
            tktk::DX12Game::disableScene(SceneId::StageSelect);
            break;
        }
        return;
    }

    // ���j���[���ڂ̕ύX�Ԋu�^�C�}�[�J�E���g���O�ȏゾ������
    if (m_changeMenuIntervalSecTimer > 0.0f)
    {
        // �J�E���g�_�E�����Ă��̊֐����I����
        m_changeMenuIntervalSecTimer -= tktk::DX12Game::deltaTime();
        return;
    }

    // ���݂̈ړ����͂��擾����
    const tktkMath::Vector2& moveInput = tktk::DX12Game::getMoveInput();

    // �������̓��͂� -0.5��菬����������
    if (moveInput.y < -0.5f)
    {
        // ���̃��j���[�̎�ނ𐮐��^�ŋ��߂�
        int nextMenuState = static_cast<int>(m_curMenuState) + 1;

        // ���̃��j���[�̔ԍ����L���Ȑ�����������
        if (nextMenuState <= static_cast<int>(MenuContantType::Back))
        {
            // �I������Ă��郁�j���[���ڂ��X�V����
            changeMenuState(nextMenuState);
        }
    }

    // �������̓��͂� 0.5���傫��������
    else if (moveInput.y > 0.5f)
    {
        // ���̃��j���[�̎�ނ𐮐��^�ŋ��߂�
        int nextMenuState = static_cast<int>(m_curMenuState) - 1;

        // ���̃��j���[�̔ԍ����L���Ȑ�����������
        if (nextMenuState >= static_cast<int>(MenuContantType::Stage1))
        {
            // �I������Ă��郁�j���[���ڂ��X�V����
            changeMenuState(nextMenuState);
        }
    }
}

void Sht2D_StageSelectSceneMenuScript::changeMenuState(int nextMenuState)
{
    // ���݂̃��j���[���ڂ̃I�u�W�F�N�g���擾����
    const tktk::GameObjectPtr& preMenuContantObject = m_menuContantObjectArray.at(static_cast<size_t>(m_curMenuState));

    // ���݂̃��j���[���ڂ̃I�u�W�F�N�g����������e�L�X�g�`��R���|�[�l���g���擾����
    tktk::ComponentPtr<tktk::TextDrawer2D> preMenuContantTextDrawer = preMenuContantObject->getComponent<tktk::TextDrawer2D>();

    // ���݂̃��j���[���ڂ̃e�L�X�g�F�𔒂ɂ���
    preMenuContantTextDrawer->setBlendRate(tktkMath::Color_v::white);

    // ���݂̃��j���[���ڂ�V�������ڂɕύX����
    m_curMenuState = static_cast<MenuContantType>(nextMenuState);

    // �V�������j���[���ڂ̃I�u�W�F�N�g���擾����
    const tktk::GameObjectPtr& nextMenuContantObject = m_menuContantObjectArray.at(static_cast<size_t>(m_curMenuState));

    // �V�������j���[���ڂ̃I�u�W�F�N�g����������e�L�X�g�`��R���|�[�l���g���擾����
    tktk::ComponentPtr<tktk::TextDrawer2D> nextMenuContantTextDrawer = nextMenuContantObject->getComponent<tktk::TextDrawer2D>();

    // �V�������j���[���ڂ̃e�L�X�g�F��Ԃɂ���
    nextMenuContantTextDrawer->setBlendRate(tktkMath::Color_v::red);

    // ���j���[���ڂ̕ύX�Ԋu�^�C�}�[���J�n����
    m_changeMenuIntervalSecTimer = ChangeMenuIntervalTimeSec;
}
