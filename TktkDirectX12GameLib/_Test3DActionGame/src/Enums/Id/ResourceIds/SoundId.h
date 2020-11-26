#ifndef SOUND_ID_H_
#define SOUND_ID_H_

enum class SoundId
{
	/* BGM */
	TitleBGM,
	GamePlayBGM,
	ResultBGM,

	/* SE */
	PlayerWalk,
	PlayerRun,
	PlayerAttack1,
	PlayerAttack2,
	PlayerJumpAttack,
	PlayerDamage,
	PlayerDead,

	FighterEnemyAttack1,
	FighterEnemyAttack2,
	FighterEnemyJumpAttack,
	FighterEnemyDamage,
	FighterEnemyDead,

	ShooterEnemyAttack,
	ShooterEnemyShot,
	ShooterEnemyDamage,
	ShooterEnemyDead,

	BossEnemyNormalAttack,
	BossEnemyJumpAttack,
	BossEnemyRollAttack,
	BossEnemyDead,

	HeavyBlow,
	LightBlow,

	HeavySword,
	MiddleSword,
	LightSword,

	Confirm,
};
#endif // !SOUND_ID_H_