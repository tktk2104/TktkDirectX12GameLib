#ifndef ACT_3D_ENEMY_ATTACK_RANGE_GENERATOR_H_
#define ACT_3D_ENEMY_ATTACK_RANGE_GENERATOR_H_

#include <TktkDX12GameLib.h>

// エネミーの攻撃判定を出現させる処理を行うコンポーネント
class Act3D_EnemyAttackRangeGenerator
	: public tktk::ComponentBase
{
public:

	Act3D_EnemyAttackRangeGenerator(float generateTimeSec, float deleteTimeSec, const tktkMath::Vector3& position, const tktkMath::Vector3& scale);

public:

	void start();
	void onEnable();
	void onDisable();
	void update();

private:

	// 攻撃判定が出現するまでの時間
	float				m_generateTimeSec;

	// 攻撃判定が消滅するまでの時間
	float				m_deleteTimeSec;

	// 攻撃判定の出現、消滅を管理するためのタイマー
	float				m_attackRangeSecTimer{ 0.0f };

	// エネミーの攻撃判定範囲オブジェクト
	tktk::GameObjectPtr m_attackRange;
};
#endif // !ACT_3D_ENEMY_ATTACK_RANGE_GENERATOR_H_