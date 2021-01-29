#ifndef SHT_2D_SPREAD_BULLET_ENEMY_BULLET_CREATOR_H_
#define SHT_2D_SPREAD_BULLET_ENEMY_BULLET_CREATOR_H_

#include <TktkDX12GameLib.h>

// �g�U�e�G�l�~�[�̒e�����R���|�[�l���g
class Sht2D_SpreadBulletEnemyBulletCreator
	: public tktk::ComponentBase
{
public:

	Sht2D_SpreadBulletEnemyBulletCreator() = default;

public:

	void start();
	void update();

private:

	// ���b�̒e�̈ړ����x
	constexpr static float	BulletSpeedPerSec			{ 512.0f };

	// ��x�ɉ����̒e�𐶐����邩�H
	constexpr static size_t CreateBulletCountPerOnce	{ 3U };

	// �e�̔��ˊԊu�^�C�}�[�i�b�j
	constexpr static float	ShotIntervalTimeSec			{ 0.1f };

	// ���˂��Ƃ̒e�̔��ˊp�̍��i�x���@�j
	constexpr static float	ShotBulletAngleDistDeg		{ 66.0f };

private:

	// ���݂̒e�̔��ˊp�̊�l�i�x���@�j
	float m_curBaseShotAngleDeg		{ 0.0f };

	// �e�̔��ˊԊu�^�C�}�[�i�b�j
	float m_shotIntervalSecTimer	{ 0.0f };

	tktk::ComponentPtr<tktk::Transform2D> m_transform;

	tktk::ComponentPtr<tktk::InertialMovement2D> m_inertialMovement;
};
#endif // !SHT_2D_SPREAD_BULLET_ENEMY_BULLET_CREATOR_H_