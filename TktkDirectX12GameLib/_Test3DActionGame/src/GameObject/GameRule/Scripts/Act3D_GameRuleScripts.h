#ifndef ACT_3D_GAME_RULE_SCRIPTS_H_
#define ACT_3D_GAME_RULE_SCRIPTS_H_

#include <array>
#include <TktkDX12GameLib.h>

class Act3D_GameRuleScripts
	: public tktk::ComponentBase
{
public:

	Act3D_GameRuleScripts() = default;

public:

	void start();
	void update();

public:

	bool isGameOver() const;

private:

	void spawnEnemyCheck();

private:

	enum class SpawnEnemyType
	{
		Fighter,
		Shooter,
		Boss
	};

private:

	constexpr static std::array<SpawnEnemyType, 3U> SpawnData
	{
		SpawnEnemyType::Fighter,
		SpawnEnemyType::Shooter,
		SpawnEnemyType::Boss
	};

private:

	bool	m_isGameOver{ false };

	bool	m_gamePlaying		{ true };
	int		m_enemySpawnCounter	{ 0 };

	bool	m_sendPlayerMessageNextFrame{ false };
	tktk::GameObjectPtr m_playerObject;
};
#endif // !ACT_3D_GAME_RULE_SCRIPTS_H_