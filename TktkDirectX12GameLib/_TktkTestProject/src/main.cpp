#include <TktkDX12GameLibDefinition.h>

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

#include <TktkDX12Game/Component/ComponentManager.h>
#include <TktkDX12Game/Component/ComponentBase.h>

#include "Scene/LoadingScene.h"
#include "Scene/MainScene.h"

#include "Enum/_ResourceIds/ResourceIds.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
{
	// �uDX12GameManager�v�̏����ݒ������
	{
		tktk::DX12GameManagerInitParam initParam{};
		{
			auto& windowParam = initParam.windowParam;

			windowParam.hInstance	= hInstance;
			windowParam.nCmdShow	= nCmdShow;
			windowParam.windowName	= "TestProject";
			windowParam.windowSize	= { 1920.0f, 1080.0f };
		}

		initParam.craeteDebugLayer = false;

		// DX12GameManager�̃Z�b�g�A�b�v
		tktk::DX12GameManager::initialize(initParam);
	}

	// �V�[����ǉ�����
	tktk::DX12GameManager::addSceneAndAttachId<LoadingScene>(SceneId::Loading);
	tktk::DX12GameManager::addSceneAndAttachId<MainScene>(SceneId::Main);

	// �ǂݍ��݃V�[����L���ɂ���
	tktk::DX12GameManager::enableScene(tktk::DX12GameManager::getSceneHandle(SceneId::Loading));

	// �Փ˔���̑g�ݍ��킹��ݒ肷��
	tktk::DX12GameManager::addCollisionGroup(1, 2);

	// �v���O�����J�n
	tktk::DX12GameManager::run();

	return 0;
}