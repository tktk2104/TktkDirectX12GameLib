#ifndef ACT_3D_BOSS_ENEMY_PARAM_H_
#define ACT_3D_BOSS_ENEMY_PARAM_H_

#include <TktkDX12GameLib.h>

// ボスエネミーの能力値のコンポーネント
class Act3D_BossEnemyParam
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyParam() = default;

public:

	void update();

public:

	// 引数の値だけHpを減らす
	void damage(int damage);
	// Hpがゼロか判別する
	bool outOfHp() const;

	// 通常攻撃のインターバルが終わっているか取得する
	bool canNormalAttack() const;
	// 通常攻撃のインターバルを設定する
	void resetNormalAttackIntervelTimer(float time);

	// 回転攻撃のインターバルが終わっているかを取得する
	bool canRollAttack() const;
	// 回転攻撃のインターバルを設定する
	void resetRollAttackIntervelTimer(float time);

	// ジャンプ攻撃のインターバルが終わっているかを取得する
	bool canJumpAttack() const;
	// ジャンプ攻撃のインターバルを設定する
	void resetJumpAttackIntervelTimer(float time);

public:

	// 最大HP
	constexpr int getMaxHp() const { return 15; }

private:

	// 現在のHp
	int		m_curHp							{ getMaxHp() };

	// 通常攻撃のインターバルタイマー
	float	m_normalAttackIntervalSecTimer	{ 0.0f };
	// 回転攻撃のインターバルタイマー
	float	m_rollAttackIntervalSecTimer	{ 0.0f };
	// ジャンプ攻撃のインターバルタイマー
	float	m_jumpAttackIntervalSecTimer	{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_PARAM_H_