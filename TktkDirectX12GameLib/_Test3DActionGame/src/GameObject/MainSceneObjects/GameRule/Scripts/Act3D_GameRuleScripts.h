#ifndef ACT_3D_GAME_RULE_SCRIPTS_H_
#define ACT_3D_GAME_RULE_SCRIPTS_H_

#include <array>
#include <TktkDX12GameLib.h>

// �Q�[�����[�����Ǘ�����R���|�[�l���g
class Act3D_GameRuleScripts
	: public tktk::ComponentBase
{
public:

	Act3D_GameRuleScripts() = default;

public:

	void start();
	void update();

public:

	// �Q�[���I�[�o�[�t���O���擾����
	bool isGameOver() const;

private:

	// �V���ȓG�̐�������Ɛ������s��
	void spawnEnemyCheck();

private:

	// ��������G�̎��
	enum class SpawnEnemyType
	{
		Fighter,
		Shooter,
		Boss
	};

private:

	// �o������G�̏��
	constexpr static std::array<SpawnEnemyType, 3U> SpawnData
	{
		SpawnEnemyType::Fighter,
		SpawnEnemyType::Shooter,
		SpawnEnemyType::Boss
	};

private:

	// �Q�[���I�[�o�[�t���O
	bool	m_isGameOver{ false };

	// �Q�[���v���C���t���O
	bool	m_gamePlaying		{ true };

	// �G�̏o�����J�E���^
	int		m_enemySpawnCounter	{ 0 };

	// ���̃t���[���Ƀv���C���[�Ƀ��b�Z�[�W�𑗐M���邩�H
	bool	m_sendPlayerMessageNextFrame{ false };

	// �v���C���[�I�u�W�F�N�g
	tktk::GameObjectPtr m_playerObject;
};
#endif // !ACT_3D_GAME_RULE_SCRIPTS_H_