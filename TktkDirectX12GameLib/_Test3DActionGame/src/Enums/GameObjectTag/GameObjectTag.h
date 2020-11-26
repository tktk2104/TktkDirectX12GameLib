#ifndef GAME_OBJECT_TAG_H_
#define GAME_OBJECT_TAG_H_

enum class GameObjectTag
{
	LoadingSceneObject,	// ���[�f�B���O�V�[���I�����ɏ��ł���I�u�W�F�N�g
	TitleSceneObject,	// �^�C�g���V�[���I�����ɏ��ł���I�u�W�F�N�g
	MainSceneObject,	// ���C���V�[���I�����ɏ��ł���I�u�W�F�N�g
	ResultSceneObject,	// ���U���g�V�[���I�����ɏ��ł���I�u�W�F�N�g


	GameRule,			// �Q�[�����[��

	Player,				// �v���C���[
	Enemy,				// �G�l�~�[
	Boss,				// �{�X

	EnemyBullet,		// �G�l�~�[�̒e

	PlayerAttackRange,	// �v���C���[�̍U���͈�
	EnemyAttackRange,	// �G�l�~�[�̍U���͈�


	PlayerCamera,		// �v���C���[�J����
};
#endif // !GAME_OBJECT_TAG_H_