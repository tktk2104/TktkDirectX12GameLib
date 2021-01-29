#ifndef SHT_2D_TANK_ENEMY_NORMAL_BULLET_CREATOR_H_
#define SHT_2D_TANK_ENEMY_NORMAL_BULLET_CREATOR_H_

#include <TktkDX12GameLib.h>

// ��ԃG�l�~�[�̒e���˃R���|�[�l���g
class Sht2D_TankEnemyNormalBulletCreator
	: public tktk::ComponentBase
{
public:

	Sht2D_TankEnemyNormalBulletCreator() = default;

public:

	void start();
	void update();

private:

	// ���b�̒e�̈ړ����x
	constexpr static float BulletSpeedPerSec	{ 512.0f };

	// �e�̔��ˊԊu�i�b�j
	constexpr static float ShotIntervalTimeSec	{ 1.0f };

private:

	// �e�̔��ˊԊu�^�C�}�[
	float m_shotIntervalSecTimer{ 0.0f };

	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !SHT_2D_TANK_ENEMY_NORMAL_BULLET_CREATOR_H_