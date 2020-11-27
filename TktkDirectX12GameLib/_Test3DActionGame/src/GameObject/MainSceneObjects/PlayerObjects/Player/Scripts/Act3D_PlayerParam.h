#ifndef ACT_3D_PLAYER_PARAM_H_
#define ACT_3D_PLAYER_PARAM_H_

#include <TktkDX12GameLib.h>

// プレイヤーの能力値のコンポーネント
class Act3D_PlayerParam
	: public tktk::ComponentBase
{
public:

	Act3D_PlayerParam() = default;

public:

	// 引数の値だけHPを減らす
	void damage(int damage);

	// HPがゼロ以下か判定する
	bool outOfHp() const;

	// 現在のHPを取得する
	int getCurHp() const;

public:

	// 最大HP
	constexpr int getMaxHp() const { return 10; }

private:

	// 現在のHP
	int m_curHp{ getMaxHp() };
};
#endif // !ACT_3D_PLAYER_PARAM_H_