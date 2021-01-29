#include "Sht2D_TitleSceneMenuScript.h"

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

void Sht2D_TitleSceneMenuScript::start()
{
  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	������R���|�[�l���g�̓����ŐV���ȃI�u�W�F�N�g����鎖���\�ł��B
    ���@�܂��A�������Ɏg�p�����utktk::GameObjectPtr�v�^�̕ϐ��̒l��ێ����鎖�ŁA���ł����̃I�u�W�F�N�g�ɃA�N�Z�X�ł���悤�ɂȂ�܂��B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

    // ���j���[�̗v�f�����A���̃|�C���^��z��ɕۑ�����
    m_menuContantObjectArray = {  
        createMenuContant(tktkMath::Vector2(0.0f,   0.0f), tktkMath::Color_v::red,      "GameStart"),
        createMenuContant(tktkMath::Vector2(0.0f, 128.0f), tktkMath::Color_v::white,    "GameEnd")
    };


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	���Q�[���I�u�W�F�N�g�͂��݂��ɐe�q�֌W�������Ƃ��ł��܂��B
    ���@�e�q�֌W�������ŁA�q�v�f���e�v�f�̍��W����ɂ��č��W�ϊ�����悤�ɂȂ�����A�e�v�f�̏�Ԃ̈ꕔ���q�������L���鎖�ɂȂ�܂��B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

    // ���j���[�̗v�f�����g�̎q�v�f�ɒǉ�����
    getGameObject()->addChild(m_menuContantObjectArray.at(0U));
    getGameObject()->addChild(m_menuContantObjectArray.at(1U));
}

void Sht2D_TitleSceneMenuScript::update()
{
  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	�����͂̌��m���s���������́A�utktk::DX12Game::isTrigger(inputType)�v�܂��́utktk::DX12Game::isPush(inputType)�v���g���ĉ������B
    ���@�����ɂ́umain.cpp�v�Őݒ肵���g���͂̎�ށh�̑��A�utktk::KeybordKeyType�v�Ȃǌʂ̓��͂̎�ނ�n�������ł��܂��B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

    // ����L�[�������ꂽ��
    if (tktk::DX12Game::isTrigger(CommandId::Decision))
    {
        auto local = m_menuContantObjectArray.at(0U)->getComponent<tktk::Transform2D>()->getLocalPosition(); // { 0.0f,   0.0f }

        auto world = m_menuContantObjectArray.at(0U)->getComponent<tktk::Transform2D>()->getWorldPosition(); // { 960.0f, 668.0f }

        // ���݂̃��j���[�̏�Ԃŕ���
        switch (m_curMenuState)
        {
        // �g�Q�[���X�^�[�g�h���ڂ��I������Ă�����
        case MenuContantType::GameStart:

            // �X�e�[�W�Z���N�g�V�[���ֈڍs
            tktk::DX12Game::enableScene(SceneId::StageSelect);
            tktk::DX12Game::disableScene(SceneId::Title);
            break;

        // �g�Q�[���I���h���ڂ��I������Ă�����
        case MenuContantType::GemeEnd:


          /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	        ���v���O�������I���������ꍇ�́u tktk::DX12Game::gameExit()�v���g���ĉ������B
            ���@���݂̃t���[���̏������I��莟��A�e�탊�\�[�X�̌�n�����I������A�v���O�������I�����܂��B
	        ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

            // �Q�[�����I������B
            tktk::DX12Game::gameExit();
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


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	���ړ����͂̌��m���s���������́A�utktk::DX12Game::getMoveInput()�v���g���ĉ������B
    ���@���̊֐��ł̓Q�[���p�b�h�̍��X�e�B�b�N�̓��͂ƁA�umain.cpp�v�Őݒ肵���uWASD�L�[�v�̓��͂��擾�ł��܂��B
    ���@����]�ړ����͂̌��m���s���������́utktk::DX12Game::getLookInput()�v���g���ĉ������B�i���̊֐��̓Q�[���p�b�h�̉E�X�e�B�b�N�ɑΉ����Ă��܂��j
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

    // ���݂̈ړ����͂��擾����
    const tktkMath::Vector2& moveInput = tktk::DX12Game::getMoveInput();

    // �������̓��͂� -0.5��菬����������
    if (moveInput.y < -0.5f)
    {
        // ���̃��j���[�̎�ނ𐮐��^�ŋ��߂�
        int nextMenuState = static_cast<int>(m_curMenuState) + 1;

        // ���̃��j���[�̔ԍ����L���Ȑ�����������
        if (nextMenuState <= static_cast<int>(MenuContantType::GemeEnd))
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
        if (nextMenuState >= static_cast<int>(MenuContantType::GameStart))
        {
            // �I������Ă��郁�j���[���ڂ��X�V����
            changeMenuState(nextMenuState);
        }
    }
}

// �I������Ă��郁�j���[���ڂ��X�V����
void Sht2D_TitleSceneMenuScript::changeMenuState(int nextMenuState)
{
    // ���݂̃��j���[���ڂ̃I�u�W�F�N�g���擾����
    const tktk::GameObjectPtr& preMenuContantObject = m_menuContantObjectArray.at(static_cast<size_t>(m_curMenuState));


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
    ������̃I�u�W�F�N�g�����R���|�[�l���g���擾�������ꍇ�́A�ugameObject->getComponent<T>()�v���g���ĉ������B
    ���@�擾�����R���|�[�l���g�́utktk::ComponentPtr<T>�v�^�̕ϐ��Ƃ��Ĉ����܂��B
    ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

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