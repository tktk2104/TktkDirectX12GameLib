#ifndef SHT_2D_PLAYER_MISSILE_CREATOR_H_
#define SHT_2D_PLAYER_MISSILE_CREATOR_H_

#include <TktkDX12GameLib.h>
#include <TktkMath/Structs/Vector2.h>
#include "Sht2D_PlayerBulletCount.h"

class Sht2D_PlayerMissileCreator
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerMissileCreator() = default;

public:

	void start();
	void update();

private:

	std::vector<tktk::GameObjectPtr> findForwardLockOnEnemy(size_t maxFindNum) const;

	void shotMissile();

private:

	// �~�T�C���̑��x�i���b�j
	constexpr static float				MissileSpeedPerSec			{ 2000.0f };

	// �~�T�C���̉����x�i���b�j
	constexpr static float				MissileAccelerationPerSec	{ 1500.0f };

	// �~�T�C�����O�i����܂ł̎��ԁi�b�j
	constexpr static float				MissileActiveTimeSec		{ 0.5f };

	// �~�T�C���̏����ړ������i���b�j
	constexpr static tktkMath::Vector2	InitVelocity				{ 32.0f, 0.0f };

	// �~�T�C���̃��b�N�I���\�p�x�i�x���@�j
	constexpr static float				MissileLockOnAngleRangeDeg	{ 45.0f };

	// �~�T�C���̃��b�N�I������
	constexpr static float				MissileLockOnTimeSec		{ 1.0f };

	// �~�T�C�����ˊԊu�i�b�j
	constexpr static float				ShotIntervalTimeSec			{ 1.0f };

private:

	// ���˓��͎��ԃ^�C�}�[
	float m_pushingSecTimer		{ 0.0f };

	// ���b�N�I�������t���O
	bool m_lockOnReady			{ false };

	// ���ˊԊu�^�C�}�[
	float m_shotIntervalSecTimer{ 0.0f };

	std::array<tktk::GameObjectPtr, 2U>			m_lockOnIconObjectArray;

	tktk::ComponentPtr<tktk::Transform2D>		m_transform;

	tktk::ComponentPtr<Sht2D_PlayerBulletCount> m_playerBulletCount;
};
#endif // !SHT_2D_PLAYER_MISSILE_CREATOR_H_