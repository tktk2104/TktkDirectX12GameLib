#ifndef COLLISION_GROUP_H_
#define COLLISION_GROUP_H_

// �Փ˔���̑g�ݍ��킹
enum class CollisionGroup
{
	None,				// �Փ˔��薳��
	Player,				// �v���C���[
	Enemy,				// �G�l�~�[
	PlayerBullet,		// �v���C���[�̒e
	EnemyBullet,		// �G�l�~�[�̒e
};
#endif // !COLLISION_GROUP_H_