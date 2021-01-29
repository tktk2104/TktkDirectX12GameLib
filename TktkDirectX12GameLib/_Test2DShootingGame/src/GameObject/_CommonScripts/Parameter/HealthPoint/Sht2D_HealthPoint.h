#ifndef SHT_2D_HEALTH_POINT_H_
#define SHT_2D_HEALTH_POINT_H_

#include <TktkDX12GameLib.h>

// 耐久力のコンポーネント
class Sht2D_HealthPoint
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_HealthPoint(float maxHp);

public:

	// 引数の値だけ耐久力を減らす
	void damage(float damage);

	// 耐久力がゼロ以下か判定する
	bool outOfHp() const;

	// 現在の耐久力を取得する
	float getCurHp() const;

	// 最大の耐久力を取得する
	float getMaxHp() const;

private:

	// 最大耐久力
	float m_maxHp;

	// 現在の耐久力
	float m_curHp;
};
#endif // !SHT_2D_HEALTH_POINT_H_