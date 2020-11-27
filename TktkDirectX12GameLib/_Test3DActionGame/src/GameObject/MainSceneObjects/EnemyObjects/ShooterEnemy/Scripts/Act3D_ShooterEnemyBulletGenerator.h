#ifndef ACT_3D_SHOOTER_ENEMY_BULLET_GENERATOR_H_
#define ACT_3D_SHOOTER_ENEMY_BULLET_GENERATOR_H_

#include <TktkDX12GameLib.h>

// �������U���G�l�~�[�̒e�𐶐�����R���|�[�l���g
class Act3D_ShooterEnemyBulletGenerator
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyBulletGenerator() = default;

public:

	void start();
	void onEnable();
	void update();

private:

	// Transform�̈ʒu����ǂꂭ�炢���ꂽ�ʒu�ɍ�邩�H
	static constexpr tktkMath::Vector3	GeneratePos{ 0.0f, 1.0f, 0.0f };

	// ���b��ɒe����邩�H
	static constexpr float				GenerateTimeSec{ 1.5f };

	// �e�̑��x�i���b�j
	static constexpr float				BulletSpeed{ 15.0f };

private:

	bool m_endShot				{ false };
	float m_generateSecTimer	{ 0.0f };
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_SHOOTER_ENEMY_BULLET_GENERATOR_H_