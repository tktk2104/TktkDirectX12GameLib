#ifndef ACT_3D_BOSS_ENEMY_START_ATTACK_H_
#define ACT_3D_BOSS_ENEMY_START_ATTACK_H_

#include <TktkDX12GameLib.h>
#include "Act3D_BossEnemyParam.h"

class Act3D_BossEnemyStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyStartAttack() = default;

public:

	void start();
	void update();

//************************************************************
private: /* 通常攻撃の能力 */

	// 攻撃開始できるプレイヤーとの角度差（度数法）
	static constexpr float NormalAttackStartAngleDeg	{ 45.0f };

	// 攻撃開始できるプレイヤーとの距離
	static constexpr float NormalAttackStartRange		{ 4.0f };

	// 同じ行動のインターバル（秒）
	static constexpr float NormalAttackIntervalTimeSec	{ 0.2f };

//************************************************************
private: /* ローリング攻撃の能力 */

	// 攻撃開始できるプレイヤーとの角度差（度数法）
	static constexpr float RollAttackStartAngleDeg		{ 45.0f };

	// ローリング攻撃を開始するプレイヤーとの距離
	static constexpr float RollAttackStartRange			{ 12.0f };

	// 同じ行動のインターバル（秒）
	static constexpr float RollAttackIntervalTimeSec	{ 7.5f };

	//// 攻撃の失敗確率（割合）
	//static constexpr float RollAttackMissRate			{ 0.1f };
	//
	//// 攻撃の最大連続成功数（この回数連続で成功した場合、次は必ず失敗する）
	//static constexpr unsigned int RollAttackMissCountMax{ 5U };

//************************************************************
private: /* ジャンプ攻撃の能力 */

	// 攻撃開始できるプレイヤーとの角度差（度数法）
	static constexpr float JumpAttackStartAngleDeg		{ 1.0f };

	// ローリング攻撃を開始するプレイヤーとの距離
	static constexpr float JumpAttackStartRange			{ 15.0f };

	// 同じ行動のインターバル（秒）
	static constexpr float JumpAttackIntervalTimeSec	{ 10.0f };

private:

	// 回転攻撃連続成功回数カウンタ
	unsigned int								m_rollAttackMissCounter	{ 0U };

	// ボスエネミーの能力値のコンポーネント
	tktk::ComponentPtr<Act3D_BossEnemyParam>	m_selfParam;

	// 自身の座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>		m_selfTransform;

	// プレイヤーの座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>		m_playerTransform;
	
};
#endif // !ACT_3D_BOSS_ENEMY_START_ATTACK_H_
