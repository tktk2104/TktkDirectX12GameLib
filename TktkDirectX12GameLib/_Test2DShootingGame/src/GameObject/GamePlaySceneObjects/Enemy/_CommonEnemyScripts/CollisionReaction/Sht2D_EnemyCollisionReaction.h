#ifndef SHT_2D_ENEMY_COLLISION_REACTION_H_
#define SHT_2D_ENEMY_COLLISION_REACTION_H_

#include <TktkDX12GameLib.h>

// �G�l�~�[�̏Փ˔��胊�A�N�V�����R���|�[�l���g
class Sht2D_EnemyCollisionReaction
	: public tktk::ComponentBase
{
public:

	Sht2D_EnemyCollisionReaction() = default;

public:

	void update();
	void onCollisionEnter(const tktk::GameObjectPtr & other);
	void onCollisionStay(const tktk::GameObjectPtr & other);

private:

	// �����G�t�F�N�g�̏o���Ԋu�i�b�j
	constexpr static float CreateExplosionIntervalTimeSec{ 0.5f };

private:

	// �����G�t�F�N�g�̏o���Ԋu�^�C�}�[�i�b�j
	float m_createExplosionIntervalSecTimer{ 0.0f };
};
#endif // !SHT_2D_ENEMY_COLLISION_REACTION_H_