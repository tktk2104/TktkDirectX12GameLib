#ifndef ACT_3D_GAME_RULE_SCRIPTS_H_
#define ACT_3D_GAME_RULE_SCRIPTS_H_

#include <array>
#include <TktkDX12GameLib.h>

// ゲームルールを管理するコンポーネント
class Act3D_GameRuleScripts
	: public tktk::ComponentBase
{
public:

	Act3D_GameRuleScripts() = default;

public:

	void start();
	void update();

public:

	// ゲームオーバーフラグを取得する
	bool isGameOver() const;

private:

	// 新たな敵の生成判定と生成を行う
	void spawnEnemyCheck();

private:

	// 生成する敵の種類
	enum class SpawnEnemyType
	{
		Fighter,
		Shooter,
		Boss
	};

private:

	// 出現する敵の情報
	constexpr static std::array<SpawnEnemyType, 3U> SpawnData
	{
		SpawnEnemyType::Fighter,
		SpawnEnemyType::Shooter,
		SpawnEnemyType::Boss
	};

private:

	// ゲームオーバーフラグ
	bool	m_isGameOver{ false };

	// ゲームプレイ中フラグ
	bool	m_gamePlaying		{ true };

	// 敵の出現数カウンタ
	int		m_enemySpawnCounter	{ 0 };

	// 次のフレームにプレイヤーにメッセージを送信するか？
	bool	m_sendPlayerMessageNextFrame{ false };

	// プレイヤーオブジェクト
	tktk::GameObjectPtr m_playerObject;
};
#endif // !ACT_3D_GAME_RULE_SCRIPTS_H_