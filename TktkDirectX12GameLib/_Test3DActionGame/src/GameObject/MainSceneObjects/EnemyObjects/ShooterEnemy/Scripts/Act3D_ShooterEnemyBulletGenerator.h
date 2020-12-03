#ifndef ACT_3D_SHOOTER_ENEMY_BULLET_GENERATOR_H_
#define ACT_3D_SHOOTER_ENEMY_BULLET_GENERATOR_H_

#include <TktkDX12GameLib.h>

// 遠距離攻撃エネミーの弾を生成するコンポーネント
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

	// Transformの位置からどれくらい離れた位置に作るか？
	static constexpr tktkMath::Vector3	GeneratePos{ 0.0f, 1.0f, 0.0f };

	// 何秒後に弾を作るか？
	static constexpr float				GenerateTimeSec{ 1.5f };

	// 弾の速度（毎秒）
	static constexpr float				BulletSpeed{ 15.0f };

private:

	bool m_endShot				{ false };
	float m_generateSecTimer	{ 0.0f };
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_SHOOTER_ENEMY_BULLET_GENERATOR_H_