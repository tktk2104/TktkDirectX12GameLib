#ifndef ACT_3D_FIGHTER_ENEMY_START_ATTACK_H_
#define ACT_3D_FIGHTER_ENEMY_START_ATTACK_H_

#include <TktkDX12GameLib.h>

// �ߋ����U���G�l�~�[�̍U���J�n�����R���|�[�l���g
class Act3D_FighterEnemyStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_FighterEnemyStartAttack() = default;

public:

	void start();
	void update();

//************************************************************
private: /* �ʏ�U���̔\�� */

	// �U���J�n�ł���v���C���[�Ƃ̊p�x���i�x���@�j
	static constexpr float NormalAttackStartAngleDeg	{ 45.0f };

	// �U���J�n�ł���v���C���[�Ƃ̋���
	static constexpr float NormalAttackStartRange		{ 3.0f };

	// �U���̃C���^�[�o���i�b�j
	static constexpr float NormalAttackIntervalTimeSec{ 1.0f };

//************************************************************
private: /* �W�����v�U���̔\�� */

	// �U���J�n�ł���v���C���[�Ƃ̊p�x���i�x���@�j
	static constexpr float JumpAttackStartAngleDeg		{ 1.0f };

	// �U���J�n�ł���v���C���[�Ƃ̋���
	static constexpr float JumpAttackStartRange			{ 7.0f };

	// �U���̃C���^�[�o���i�b�j
	static constexpr float JumpAttackIntervalTimeSec	{ 1.5f };

private:

	// �U���Ԋu���Ǘ�����^�C�}�[
	float									m_attackIntervelSecTimer{ 0.0f };

	// ���g�̍��W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;

	// �v���C���[�̍��W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_FIGHTER_ENEMY_START_ATTACK_H_
