#ifndef SPRITE_ID_H_
#define SPRITE_ID_H_

// �X�v���C�g���\�[�X�T�E���h
enum class SpriteId
{
	Player,				// �v���C���[�摜
	PlayerNormalBullet,	// �v���C���[�ʏ�e�摜

	Missile,			// �~�T�C���摜
	BompFrame,			// �{���̊O�g�摜
	BompCore,			// �{���̃R�A�摜

	TankEnemyBase,		// ��ԃG�l�~�[�̓��̉摜
	TankEnemyTop,		// ��ԃG�l�~�[�̖C���摜

	SpreadBulletEnemy,	// �g�U�e�G�l�~�[�摜

	Flame,				// ���̉摜

	Spark,				// �ėp�G�t�F�N�g�摜
	Explosion,			// �����摜

	LockOnTarget,		// ���b�N�I���Ώۉ摜
	LockOnReady,		// ���b�N�I�������摜

	StreamingLine,		// �w�i�̐�

	BackGround_Base_1,	// ��n�w�i�摜�P
	BackGround_Base_2,	// ��n�w�i�摜�Q

	HpBarBackGround,	// �̗̓o�[�̔w�i�摜
	HpBarFrame,			// �̗̓o�[�̊O�g�摜
	HpBarContent,		// �̗̓o�[�̒��g�摜

	MissileCounterIcon,	// �~�T�C���̎c���摜
	BompCounterIcon,	// �{���̎c���摜
};
#endif // !SPRITE_ID_H_