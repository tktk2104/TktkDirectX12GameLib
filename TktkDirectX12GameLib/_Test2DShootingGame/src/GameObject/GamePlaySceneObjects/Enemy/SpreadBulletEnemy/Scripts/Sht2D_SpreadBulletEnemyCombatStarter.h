#ifndef SHT_2D_SPREAD_BULLET_ENEMY_COMBAT_STARTER_H_
#define SHT_2D_SPREAD_BULLET_ENEMY_COMBAT_STARTER_H_

#include <TktkDX12GameLib.h>

// �g�U�e�G�l�~�[�̐퓬�J�n�R���|�[�l���g
class Sht2D_SpreadBulletEnemyCombatStarter
	: public tktk::ComponentBase
{
public:

	Sht2D_SpreadBulletEnemyCombatStarter() = default;

public:

	void start();
	void update();

private:

	// �퓬���J�n���邙���W
	constexpr static float StartCombatYPos	{ 128.0f };

private:

	tktk::ComponentPtr<tktk::Transform2D>			m_transform;
};
#endif // !SHT_2D_SPREAD_BULLET_ENEMY_COMBAT_STARTER_H_