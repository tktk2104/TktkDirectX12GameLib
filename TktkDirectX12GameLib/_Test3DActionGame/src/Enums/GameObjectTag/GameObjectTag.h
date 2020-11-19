#ifndef GAME_OBJECT_TAG_H_
#define GAME_OBJECT_TAG_H_

enum class GameObjectTag
{
	LoadingSceneObject,	// ���[�f�B���O�V�[���ł̂ݐ�������I�u�W�F�N�g
	TitleSceneObject,	// �^�C�g���V�[���ł̂ݐ�������I�u�W�F�N�g
	MainSceneObject,	// ���C���V�[���ł̂ݐ�������I�u�W�F�N�g


	Player,				// �v���C���[
	Enemy,				// �G�l�~�[
	Boss,				// �{�X

	EnemyBullet,		// �G�l�~�[�̒e

	PlayerAttackRange,	// �v���C���[�̍U���͈�
	EnemyAttackRange,	// �G�l�~�[�̍U���͈�
};
#endif // !GAME_OBJECT_TAG_H_