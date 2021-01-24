#ifndef GAME_OBJECT_TAG_H_
#define GAME_OBJECT_TAG_H_

// �Q�[���I�u�W�F�N�g�����ʂ��邽�߂̃^�O
enum class GameObjectTag
{
	LoadingSceneObject,		// ���[�f�B���O�V�[���I�����ɏ��ł���I�u�W�F�N�g
	TitleSceneObject,		// �^�C�g���V�[���I�����ɏ��ł���I�u�W�F�N�g
	StageSelectSceneObject,	// �X�e�[�W�Z���N�g�V�[���I�����ɏ��ł���I�u�W�F�N�g
	GamePlaySceneObject,	// �Q�[���v���C�V�[���I�����ɏ��ł���I�u�W�F�N�g
	Stage1SceneObject,		// �X�e�[�W�P�V�[���I�����ɏ��ł���I�u�W�F�N�g
	Stage2SceneObject,		// �X�e�[�W�Q�V�[���I�����ɏ��ł���I�u�W�F�N�g
	Stage3SceneObject,		// �X�e�[�W�R�V�[���I�����ɏ��ł���I�u�W�F�N�g
	ResultSceneObject,		// ���U���g�V�[���I�����ɏ��ł���I�u�W�F�N�g

	GameRule,				// �Q�[�����[��
	ObjectSpawner,			// �I�u�W�F�N�g�X�|�i�[
	BaseBackGroundSpawner,	// ��n�̔w�i�X�|�i�[

	Player,					// �v���C���[
	Enemy,					// �G�l�~�[
	Boss,					// �{�X

	PlayerAttackRange,		// �v���C���[�̍U���͈�
	EnemyAttackRange,		// �G�l�~�[�̍U���͈�
};
#endif // !GAME_OBJECT_TAG_H_