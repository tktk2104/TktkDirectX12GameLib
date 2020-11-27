#ifndef ACT_3D_FIGHTER_ENEMY_PARAM_H_
#define ACT_3D_FIGHTER_ENEMY_PARAM_H_

#include <TktkDX12GameLib.h>

// 近距離攻撃エネミーの能力値のコンポーネント
class Act3D_FighterEnemyParam
	: public tktk::ComponentBase
{
public:

	Act3D_FighterEnemyParam() = default;

public:

	// 引数の値だけHPを減らす
	void damage(int damage);

	// Hpがゼロか判定する
	bool outOfHp() const;

public:

	// 最大HP
	constexpr int getMaxHp() const { return 8; }

private:

	// 現在のHp
	int m_curHp{ getMaxHp() };
};
#endif // !ACT_3D_FIGHTER_ENEMY_PARAM_H_