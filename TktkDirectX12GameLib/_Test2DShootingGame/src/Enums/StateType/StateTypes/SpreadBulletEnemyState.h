#ifndef SPREAD_BULLET_ENEMY_STATE_H_
#define SPREAD_BULLET_ENEMY_STATE_H_

enum class SpreadBulletEnemyState
{
	/* ��{�X�e�[�g */
	Alive,	// �����X�e�[�g
	Dead,	// ���S�X�e�[�g

	/* �����X�e�[�g */
	Entry,
	Combat,
};
#endif // !SPREAD_BULLET_ENEMY_STATE_H_