#ifndef COLLISION_GROUP_H_
#define COLLISION_GROUP_H_

// �Փ˔���̑g�ݍ��킹
enum class CollisionGroup
{
	None,				// �Փ˔��薳��
	Player,				// �v���C���[
	Enemy,				// �G�l�~�[
	PlayerDamageRange,	// �v���C���[�̍U���͈�
	EnemyDamageRange,	// �G�l�~�[�̍U���͈�
	Stage				// �X�e�[�W
};
#endif // !COLLISION_GROUP_H_