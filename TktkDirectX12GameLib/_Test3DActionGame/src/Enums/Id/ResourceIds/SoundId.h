#ifndef SOUND_ID_H_
#define SOUND_ID_H_

// �T�E���h���\�[�XID
enum class SoundId
{
	/* BGM */
	TitleBGM,		// �^�C�g��BGM
	GamePlayBGM,	// �Q�[���v���CBGM
	ResultBGM,		// ���U���gBGM

	/* SE */
	PlayerWalk,			// �v���C���[�����T�E���h
	PlayerRun,			// �v���C���[����T�E���h
	PlayerAttack1,		// �v���C���[��i�ڍU���T�E���h
	PlayerAttack2,		// �v���C���[��i�ڍU���T�E���h
	PlayerJumpAttack,	// �v���C���[�W�����v�U���T�E���h
	PlayerDamage,		// �v���C���[�_���[�W�T�E���h
	PlayerDead,			// �v���C���[���S�T�E���h

	FighterEnemyAttack1,	// �ߋ����U���G�l�~�[��i�ڍU���T�E���h
	FighterEnemyAttack2,	// �ߋ����U���G�l�~�[��i�ڍU���T�E���h
	FighterEnemyJumpAttack,	// �ߋ����U���G�l�~�[�W�����v�U���T�E���h
	FighterEnemyDamage,		// �ߋ����U���G�l�~�[�_���[�W�T�E���h
	FighterEnemyDead,		// �ߋ����U���G�l�~�[���S�T�E���h

	ShooterEnemyAttack,	// �������U���G�l�~�[�ߋ����U���T�E���h
	ShooterEnemyShot,	// �������U���G�l�~�[�������U���T�E���h
	ShooterEnemyDamage,	// �������U���G�l�~�[�_���[�W�T�E���h
	ShooterEnemyDead,	// �������U���G�l�~�[���S�T�E���h

	BossEnemyNormalAttack,	// �{�X�G�l�~�[�ʏ�U���T�E���h
	BossEnemyJumpAttack,	// �{�X�G�l�~�[�W�����v�U���T�E���h
	BossEnemyRollAttack,	// �{�X�G�l�~�[��]�U���T�E���h
	BossEnemyDead,			// �{�X�G�l�~�[���S�T�E���h

	HeavyBlow,		// �d�����Ō����T�E���h
	LightBlow,		// �y���Ō����T�E���h

	HeavySword,		// �d�����a�����T�E���h
	MiddleSword,	// ���ʂ̎a�����T�E���h
	LightSword,		// �y���a�����T�E���h

	Confirm,		// ����T�E���h
};
#endif // !SOUND_ID_H_