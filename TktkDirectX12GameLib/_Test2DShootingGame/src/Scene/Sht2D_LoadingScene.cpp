#include "Sht2D_LoadingScene.h"

#include "../Enums/Id/ResourceIds.h"

void Sht2D_LoadingScene::start()
{
  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	���t�H���g��ǂݍ��ޏ����́utktk::DX12Game::createFont(fontId, fontFilePath, fontName)�v�ōs���܂��B
	���@�ǂݍ��߂�t�H���g�t�@�C���̎�ނ́u.ttf�v�Ɓu.otf�v�`���ł��B
	���@���uFontId�v�͎����ō��񋓌^�ł��B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

	// �t�H���g��ǂݍ��ށi�t�H���gID�A�t�H���g�t�@�C���p�X�A�t�H���g���j
	tktk::DX12Game::createFont(FontId::Basic, "res/font/x12y20pxScanLine.ttf", "x12y20pxScanLine");


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	���e�N�X�`������X�v���C�g����鏈���́utktk::DX12Game::loadSprite(spriteId, drawPriority, textureFilePath)�v�ōs���܂��B
	���@�ǂݍ��߂�e�N�X�`���t�@�C���̎�ނ́u.png�v�Ɓu.dds�v�`���ł��B
	���@���uSpriteId�v�͎����ō��񋓌^�ł��B
	���@����Q�����̒l���������������̃��C���[�ɕ`�悳��܂��B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

	// �X�v���C�g��ǂݍ��ށi�X�v���C�gID�A�`��D��x�A�摜�t�@�C���p�X�j
	tktk::DX12Game::loadSprite(SpriteId::Player,				20.0f,		"res/image/Sht2D_Player.png");
	tktk::DX12Game::loadSprite(SpriteId::PlayerNormalBullet,	10.0f,		"res/image/Sht2D_PlayerNormalBullet.png");
	tktk::DX12Game::loadSprite(SpriteId::Missile,				10.0f,		"res/image/Sht2D_Missile.png");
	tktk::DX12Game::loadSprite(SpriteId::BompFrame,				10.0f,		"res/image/Sht2D_Bomb_Frame.png");
	tktk::DX12Game::loadSprite(SpriteId::BompCore,				11.0f,		"res/image/Sht2D_Bomb_Core.png");
	tktk::DX12Game::loadSprite(SpriteId::TankEnemyBase,			0.0f,		"res/image/Sht2D_TankEnemy_Base.png");
	tktk::DX12Game::loadSprite(SpriteId::TankEnemyTop,			1.0f,		"res/image/Sht2D_TankEnemy_Top.png");
	tktk::DX12Game::loadSprite(SpriteId::SpreadBulletEnemy,		0.0f,		"res/image/Sht2D_SpreadBulletEnemy.png");
	tktk::DX12Game::loadSprite(SpriteId::Flame,					-10.0f,		"res/image/Sht2D_Flame.png");
	tktk::DX12Game::loadSprite(SpriteId::Spark,					30.0f,		"res/image/spark.png");
	tktk::DX12Game::loadSprite(SpriteId::Explosion,				40.0f,		"res/image/explosion.png");
	tktk::DX12Game::loadSprite(SpriteId::LockOnTarget,			90.0f,		"res/image/Sht2D_LockOnTarget.png");
	tktk::DX12Game::loadSprite(SpriteId::LockOnReady,			90.0f,		"res/image/Sht2D_LockOnReady.png");
	tktk::DX12Game::loadSprite(SpriteId::HpBarBackGround,		100.0f,		"res/image/Sht2D_HpBar_BackGround.png");
	tktk::DX12Game::loadSprite(SpriteId::HpBarContent,			101.0f,		"res/image/Sht2D_HpBar_Content.png");
	tktk::DX12Game::loadSprite(SpriteId::HpBarFrame,			102.0f,		"res/image/Sht2D_HpBar_Frame.png");
	tktk::DX12Game::loadSprite(SpriteId::StreamingLine,			-110.0f,	"res/image/spark.png");
	tktk::DX12Game::loadSprite(SpriteId::BackGround_Base_1,		-100.0f,	"res/image/Sht2D_BackGround_EnemyBase_1.png");
	tktk::DX12Game::loadSprite(SpriteId::BackGround_Base_2,		-100.0f,	"res/image/Sht2D_BackGround_EnemyBase_2.png");
	tktk::DX12Game::loadSprite(SpriteId::MissileCounterIcon,	100.0f,		"res/image/Sht2D_Missile.png");
	tktk::DX12Game::loadSprite(SpriteId::BompCounterIcon,		100.0f,		"res/image/Sht2D_Bomb_Frame.png");


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	���T�E���h��ǂݍ��ޏ����́utktk::DX12Game::loadSound(soundId, soundFilePath)�v�ōs���܂��B
	���@�ǂݍ��߂�T�E���h�t�@�C���̎�ނ́u.wav�v�`���ł��B
	���@���uSoundId�v�͎����ō��񋓌^�ł��B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

	// �T�E���h��ǂݍ��ށi�T�E���hID�A�T�E���h�t�@�C���p�X�j
	tktk::DX12Game::loadSound(SoundId::ShotSE,	"res/sound/Sht2D_Shot.wav");


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	���V�[���𖳌��ɂ���ɂ́utktk::DX12Game::disableScene(sceneId)�v�ōs���܂��B
	���@�܂��A�utktk::DX12GameManager::disableScene(tktk::DX12GameManager::getSceneHandle(sceneId)�v�ł��s���܂��B
	���@�����̃t���[�����[�N�͕����̃V�[���𓯎��ɋN���ł���d�l�Ȃ��߁A�V�[���̖�����������������Ə����K�v������܂��B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

	// �ǂݍ��݃V�[���𖳌��ɂ���
	tktk::DX12Game::disableScene(SceneId::Loading);

	// �^�C�g���V�[����L���ɂ���
	tktk::DX12Game::enableScene(SceneId::Title);
}
