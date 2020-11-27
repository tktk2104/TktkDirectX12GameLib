#ifndef ACT_3D_SHOOTER_ENEMY_PARAM_H_
#define ACT_3D_SHOOTER_ENEMY_PARAM_H_

#include <TktkDX12GameLib.h>

// 遠距離攻撃エネミーの能力値のコンポーネント
class Act3D_ShooterEnemyParam
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyParam() = default;

public:

	// 引数の値分HPを減らす
	void damage(int damage);

	// HPがゼロか判別する
	bool outOfHp() const;

public:

	// 最大HP
	constexpr int getMaxHp() const { return 5; }

private:

	// 現在のHP
	int m_curHp{ getMaxHp() };
};
#endif // !ACT_3D_SHOOTER_ENEMY_PARAM_H_
