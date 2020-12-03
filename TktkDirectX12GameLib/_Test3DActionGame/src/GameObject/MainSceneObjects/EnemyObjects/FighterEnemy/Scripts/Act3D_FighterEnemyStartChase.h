#ifndef ACT_3D_FIGHTER_ENEMY_START_CHASE_H_
#define ACT_3D_FIGHTER_ENEMY_START_CHASE_H_

#include <TktkDX12GameLib.h>

// �ߋ����U���G�l�~�[�̈ړ����J�n���鏈�����s���R���|�[�l���g
class Act3D_FighterEnemyStartChase
	: public tktk::ComponentBase
{
public:

	Act3D_FighterEnemyStartChase() = default;

public:

	void start();
	void update();

private:

	// �v���C���[�𔭌��ł��鋗��
	static constexpr float FindPlayerRange		{ 30.0f };

	// �v���C���[�𔭌��ł���g�^�ォ�猩���u�G�l�~�[�̐��ʃx�N�g���ƁA�v���C���[�����̃x�N�g���v�̊Ԃ̊p�h�̍ő�l�i�x���@�j
	static constexpr float FindPlayerAngleDeg	{ 110.0f };

private:

	// ���g�̍��W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;

	// �v���C���[�̍��W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_FIGHTER_ENEMY_START_CHASE_H_