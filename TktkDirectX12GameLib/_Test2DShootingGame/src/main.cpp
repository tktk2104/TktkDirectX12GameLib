#include <TktkDX12GameLibDefinition.h>

#include <Windows.h>
#undef min
#undef max

#include <TktkDX12GameLibInitializer.h>

#include "Scene/Sht2D_LoadingScene.h"
#include "Scene/Sht2D_TitleScene.h"
#include "Scene/Sht2D_StageSelectScene.h"
#include "Scene/Sht2D_GamePlayScene.h"
#include "Scene/Sht2D_ResultScene.h"
#include "Scene/StageScene/Sht2D_Stage1Scene.h"
#include "Scene/StageScene/Sht2D_Stage2Scene.h"
#include "Scene/StageScene/Sht2D_Stage3Scene.h"
#include "Enums/Enums.h"

namespace
{
	// �uDX12GameManager�v�̏����ݒ������
	inline void setUpDX12GameManager(HINSTANCE hInstance, int nCmdShow)
	{
	  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
		��TktkLib�̏������ɕK�v�ȏ��́utktk::DX12GameManagerInitParam�v�\���̂ɋl�܂��Ă��܂��B
		��	����R�̕ϐ�������܂����A�Œ���̏��{���̐����͈ȉ��̃R�����g�̒ʂ�ł��B
		����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/
		
		tktk::DX12GameManagerInitParam initParam{};

		// WinMain�֐��̈��������̂܂ܓn��
		initParam.windowParam.hInstance		= hInstance;
		initParam.windowParam.nCmdShow		= nCmdShow;
		// �Q�[���E�B���h�E�̖��O
		initParam.windowParam.windowName	= "Test2DShootingGame";
		// �t���X�N���[���t���O
		initParam.windowParam.fullScreen	= false;
		// �Q�[����ʂ̉𑜓x
		initParam.windowParam.windowSize	= { 1920.0f, 1080.0f };

		// �f�o�b�N���C���[�𖳌��ɂ���
		initParam.createDebugLayer = false;

		// DX12GameManager�̃Z�b�g�A�b�v
		tktk::DX12GameManager::initialize(initParam);
	}
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
{
	// �uDX12GameManager�v�̏����ݒ������
	setUpDX12GameManager(hInstance, nCmdShow);


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	�������̎�ނ̓��́i�L�[�{�[�hor�Q�[���p�b�h�Ȃǁj�������������́A�utktk::DX12GameManager::addCommand(commandId, inputType)�v�Őݒ�ł��܂��B
	���Q�[���p�b�h�̃A�i���O�X�e�B�b�N���͂Ƃ��̑��̓��͂Ɍ݊����������������ꍇ�́utktk::DX12GameManager::addDirectionCommand(directionCommand, inputType)�v�Őݒ�ł��܂��B
	���@���uCommandId�v�͎����ō��񋓌^�A�utktk::DirectionCommandId�v�͎��O�ɗp�ӂ��ꂽ�񋓌^�ɂȂ�܂��B
	���@���ݒ�\�ȓ��͂́utktk::KeybordKeyType�v�ŃL�[�{�[�h���́A�utktk::GamePadBtnType�v�ŃQ�[���p�b�h���́A�utktk::MouseBtnType�v�Ń}�E�X���͂ł��B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/
	
	// �e���͂Ɠ��̓R�}���h�����т���i���̓R�}���h�̎�ށA�Ή�������́j
	tktk::DX12GameManager::addCommand(CommandId::Decision,		tktk::KeybordKeyType::key_Space);
	tktk::DX12GameManager::addCommand(CommandId::Decision,		tktk::KeybordKeyType::key_Return);
	tktk::DX12GameManager::addCommand(CommandId::Decision,		tktk::GamePadBtnType::btn_A);
	tktk::DX12GameManager::addCommand(CommandId::ShotBullet,	tktk::KeybordKeyType::key_Space);
	tktk::DX12GameManager::addCommand(CommandId::ShotBullet,	tktk::GamePadBtnType::btn_A);
	tktk::DX12GameManager::addCommand(CommandId::ShotMissile,	tktk::KeybordKeyType::key_M);
	tktk::DX12GameManager::addCommand(CommandId::ShotMissile,	tktk::GamePadBtnType::btn_B);
	tktk::DX12GameManager::addCommand(CommandId::ShotBomb,		tktk::KeybordKeyType::key_B);
	tktk::DX12GameManager::addCommand(CommandId::ShotBomb,		tktk::GamePadBtnType::btn_X);

	// �e���͂ƈړ������R�}���h�����т���i�ړ������R�}���h�̎�ށA�Ή�������́j
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveUp,	tktk::KeybordKeyType::key_W);
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveDown,	tktk::KeybordKeyType::key_S);
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveLeft,	tktk::KeybordKeyType::key_A);
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveRight, tktk::KeybordKeyType::key_D);
	

  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	���Փ˔���̑g�ݍ��킹�̒ǉ��́utktk::DX12GameManager::addCollisionGroup(collisionGroup, collisionGroup)�v�ōs���܂��B
	���@���Փ˔���O���[�v�͏Փ˔���R���|�[�l���g���g�p���鎞�Ɏg���܂��B�i�ڂ��������͕ʃt�@�C���Q�Ɓj
	���@���uCollisionGroup�v�͎����ō��񋓌^�ł��B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

	// �Փ˔���̑g�ݍ��킹��ݒ肷��i�P�߂̏Փ˔���O���[�v�A�Q�߂̏Փ˔���O���[�v�j
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::Player,		CollisionGroup::Enemy);
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::PlayerBullet,	CollisionGroup::Enemy);
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::EnemyBullet,	CollisionGroup::Player);


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	���V�[���̐ݒ�́utktk::DX12GameManager::addSceneAndAttachId(SceneId, SceneInitParam)�v�ōs���܂��B
	���@���utktk::SceneInitParam�v�͎��O�ɗp�ӂ��ꂽ�\���̂ŁA��p�̊֐��́utktk::SceneInitParam::create<SceneType>(constructorArgs...)�v�ō쐬���ĉ������B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

	// �V�[����ǉ�����i�V�[���̎�ށA�V�[���̏������\���́j
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::Loading,		tktk::SceneInitParam::create<Sht2D_LoadingScene>());
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::Title,			tktk::SceneInitParam::create<Sht2D_TitleScene>());
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::StageSelect,	tktk::SceneInitParam::create<Sht2D_StageSelectScene>());
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::GamePlay,		tktk::SceneInitParam::create<Sht2D_GamePlayScene>());
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::Stage1,			tktk::SceneInitParam::create<Sht2D_Stage1Scene>());
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::Stage2,			tktk::SceneInitParam::create<Sht2D_Stage2Scene>());
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::Stage3,			tktk::SceneInitParam::create<Sht2D_Stage3Scene>());
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::Result,			tktk::SceneInitParam::create<Sht2D_ResultScene>());
	

  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	���V�[���̏I�����ɓ���̃Q�[���I�u�W�F�N�g�i�Q�[���̗v�f�j���폜���������͎��O�Ɂutktk::DX12GameManager::setSceneEndDestroyGameObjectTag(sceneHandle, objectTag)�v�Őݒ肵�ĉ������B
	���@���������́uSceneId�v�ł͂Ȃ��A�g�V�[���n���h���h�Ȃ̂Œ��ӂ��܂��傤�B�utktk::DX12GameManager::getSceneHandle(SceneId)�v�Ŏ擾�ł��܂��B
	���@���uGameObjectTag�v�͎����ō��񋓌^�ŁA�ݒ肵���^�C�~���O�ō폜�������Q�[���I�u�W�F�N�g�ɕK���ǉ����ĉ������B�i�ǉ����@�͕ʃt�@�C���Q�Ɓj
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

	// ���ꂼ��̃V�[���̏I�����ɏ�����I�u�W�F�N�g�ɕt����^�O��ݒ肷��
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::Loading),		GameObjectTag::LoadingSceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::Title),		GameObjectTag::TitleSceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::StageSelect), GameObjectTag::StageSelectSceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::GamePlay),	GameObjectTag::GamePlaySceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::Stage1),		GameObjectTag::Stage1SceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::Stage2),		GameObjectTag::Stage2SceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::Stage3),		GameObjectTag::Stage3SceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::Result),		GameObjectTag::ResultSceneObject);
	

  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	���V�[����L���ɂ���ɂ́utktk::DX12GameManager::enableScene(sceneHandle)�v�ōs���܂��B
	��	���������́uSceneId�v�ł͂Ȃ��A�g�V�[���n���h���h�Ȃ̂Œ��ӂ��܂��傤�B�utktk::DX12GameManager::getSceneHandle(SceneId)�v�Ŏ擾�ł��܂��B
	���܂��A�utktk::DX12Game::enableScene(SceneId)�v�ł��s���܂��B�i�������SceneId�w��ɂȂ�܂��B�j
	���utktk::DX12GameManager�v�̓��C���}�l�[�W���[�A�utktk::DX12Game�v�̓��C���}�l�[�W���[�̏����������₷������ׂ̃C���^�[�t�F�[�X�ł��B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

	// �ǂݍ��݃V�[����L���ɂ���
	tktk::DX12GameManager::enableScene(tktk::DX12GameManager::getSceneHandle(SceneId::Loading));
	

/*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
  ���ȉ��̊֐����ĂԂƃt���[�����[�N�������n�߂܂�
  ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

	// �v���O�����J�n
	tktk::DX12GameManager::run();

	return 0;
}