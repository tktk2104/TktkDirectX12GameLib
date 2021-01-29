#ifndef SHT_2D_TANK_ENEMY_TOP_ROTATOR_H_
#define SHT_2D_TANK_ENEMY_TOP_ROTATOR_H_

#include <TktkDX12GameLib.h>

// ��Ԃ̖C���̉�]�R���|�[�l���g
class Sht2D_TankEnemyTopRotator
	: public tktk::ComponentBase
{
public:

	Sht2D_TankEnemyTopRotator() = default;

public:

	void start();
	void update();

private:

	// ��]����W�̃I�t�Z�b�g�l�i�Ȃ񂿂���ĕ΍��ˌ��j
	constexpr static tktkMath::Vector2 TargetOffset	{ 0.0f, -64.0f };

	// ���b�̍ő��]���i�x���@�j
	constexpr static float RotateSpeedPerSecDeg		{ 30.0f };

private:

	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !SHT_2D_TANK_ENEMY_TOP_ROTATOR_H_
