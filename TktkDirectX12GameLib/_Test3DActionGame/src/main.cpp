#include <TktkDX12GameLibDefinition.h>

#include <Windows.h>
#undef min
#undef max

#include <TktkDX12GameLibInitializer.h>

#include "Scene/Act3D_LoadingScene.h"
#include "Scene/Act3D_TitleScene.h"
#include "Scene/Act3D_MainScene.h"
#include "Scene/Act3D_ResultScene.h"

#include "Enums/Enums.h"

// �uDX12GameManager�v�̏����ݒ������
inline void setUpDX12GameManager(HINSTANCE hInstance, int nCmdShow)
{
	tktk::DX12GameManagerInitParam initParam{};

	// �Q�[���E�B���h�E�̐ݒ�
	initParam.windowParam.hInstance		= hInstance;
	initParam.windowParam.nCmdShow		= nCmdShow;
	initParam.windowParam.windowName	= "Test3DActionGame";
	initParam.windowParam.windowSize	= { 1920.0f, 1080.0f };

	// �f�o�b�N���C���[�𖳌��ɂ���
	initParam.craeteDebugLayer = false;

	// DX12GameManager�̃Z�b�g�A�b�v
	tktk::DX12GameManager::initialize(initParam);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
{
	// �uDX12GameManager�v�̏����ݒ������
	setUpDX12GameManager(hInstance, nCmdShow);

	// �e���͂Ɠ��̓R�}���h�����т���
	tktk::DX12GameManager::addCommand(CommandId::Any,			tktk::KeybordKeyType::key_W);
	tktk::DX12GameManager::addCommand(CommandId::Any,			tktk::KeybordKeyType::key_A);
	tktk::DX12GameManager::addCommand(CommandId::Any,			tktk::KeybordKeyType::key_S);
	tktk::DX12GameManager::addCommand(CommandId::Any,			tktk::KeybordKeyType::key_D);
	tktk::DX12GameManager::addCommand(CommandId::Any,			tktk::KeybordKeyType::key_Left);
	tktk::DX12GameManager::addCommand(CommandId::Any,			tktk::KeybordKeyType::key_Right);
	tktk::DX12GameManager::addCommand(CommandId::Any,			tktk::KeybordKeyType::key_Lshift);
	tktk::DX12GameManager::addCommand(CommandId::Any,			tktk::KeybordKeyType::key_Rshift);
	tktk::DX12GameManager::addCommand(CommandId::Any,			tktk::KeybordKeyType::key_Space);

	tktk::DX12GameManager::addCommand(CommandId::Run,		tktk::KeybordKeyType::key_Lshift);
	tktk::DX12GameManager::addCommand(CommandId::Run,		tktk::KeybordKeyType::key_Rshift);

	tktk::DX12GameManager::addCommand(CommandId::LookEnemy, tktk::KeybordKeyType::key_Tab);

	tktk::DX12GameManager::addCommand(CommandId::Dodge,		tktk::KeybordKeyType::key_Return);
	tktk::DX12GameManager::addCommand(CommandId::Attack,	tktk::KeybordKeyType::key_Space);

	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveUp,	tktk::KeybordKeyType::key_W);
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveDown,	tktk::KeybordKeyType::key_S);
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveLeft,	tktk::KeybordKeyType::key_A);
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveRight, tktk::KeybordKeyType::key_D);

	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::LookLeft,	tktk::KeybordKeyType::key_Left);
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::LookRight, tktk::KeybordKeyType::key_Right);

	// �V�[����ǉ�����
	auto loadingSceneHandle = tktk::DX12GameManager::addSceneAndAttachId(SceneId::Loading,	tktk::SceneInitParam::create<Act3D_LoadingScene>());
	auto titleSceneHandle	= tktk::DX12GameManager::addSceneAndAttachId(SceneId::Title,	tktk::SceneInitParam::create<Act3D_TitleScene>());
	auto mainSceneHandle	= tktk::DX12GameManager::addSceneAndAttachId(SceneId::Main,		tktk::SceneInitParam::create<Act3D_MainScene>());
	auto resultSceneHandle	= tktk::DX12GameManager::addSceneAndAttachId(SceneId::Result,	tktk::SceneInitParam::create<Act3D_ResultScene>());

	// ���ꂼ��̃V�[���̏I�����ɏ�����I�u�W�F�N�g�ɕt����^�O��ݒ肷��
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(loadingSceneHandle,	GameObjectTag::LoadingSceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(titleSceneHandle,	GameObjectTag::TitleSceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(mainSceneHandle,		GameObjectTag::MainSceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(resultSceneHandle,	GameObjectTag::ResultSceneObject);

	// �ǂݍ��݃V�[����L���ɂ���
	tktk::DX12GameManager::enableScene(loadingSceneHandle);

	// �Փ˔���̑g�ݍ��킹��ݒ肷��
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::Player,	CollisionGroup::Stage);
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::Enemy,		CollisionGroup::Stage);
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::Player,	CollisionGroup::Enemy);
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::Player,	CollisionGroup::EnemyDamageRange);
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::Enemy,		CollisionGroup::PlayerDamageRange);

	// �v���O�����J�n
	tktk::DX12GameManager::run();

	return 0;
}