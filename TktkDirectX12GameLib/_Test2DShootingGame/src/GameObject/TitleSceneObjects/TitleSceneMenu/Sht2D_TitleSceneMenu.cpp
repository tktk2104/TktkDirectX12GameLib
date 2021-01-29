#include "Sht2D_TitleSceneMenu.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Sht2D_TitleSceneMenuScript.h"

tktk::GameObjectPtr Sht2D_TitleSceneMenu::create()
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �^�C�g���V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::TitleSceneObject);

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition((tktk::DX12Game::getDrawGameAreaSize() / 2.0f) + tktkMath::Vector2(0.0f, 128.0f))
        .create();


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	������̃R���|�[�l���g�̒ǉ��́ugameObject.createComponent<ComponentType>(constructorArgs...)�v�ōs���܂��B
    ���@������R���|�[�l���g�̍쐬���@�͎��Ő������܂��B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
    �����́uSht2D_TitleSceneMenuScript�v���V���O���N���b�N��F12�L�[����͂��ă\�[�X�t�@�C���ɔ��ŉ������B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

    // �^�C�g�����j���[�X�N���v�g
    gameObject->createComponent<Sht2D_TitleSceneMenuScript>();

    return gameObject;
}
