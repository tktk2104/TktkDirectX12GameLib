#ifndef SHT_2D_HEALTH_POINT_H_
#define SHT_2D_HEALTH_POINT_H_

#include <TktkDX12GameLib.h>

class Sht2D_HealthPoint
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_HealthPoint(float maxHp);

public:

	// 引数の値だけHPを減らす
	void damage(float damage);

	// HPがゼロ以下か判定する
	bool outOfHp() const;

	// 現在のHPを取得する
	float getCurHp() const;

	// 最大のHPを取得する
	float getMaxHp() const;

private:

	float m_maxHp;

	float m_curHp;
};
#endif // !SHT_2D_HEALTH_POINT_H_