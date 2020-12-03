#ifndef ACT_3D_JAMP_ATTACK_MOVING_H_
#define ACT_3D_JAMP_ATTACK_MOVING_H_

#include <TktkDX12GameLib.h>

// �W�����v�U���̈ړ����s���R���|�[�l���g
class Act3D_JampAttackMoving
	: public tktk::ComponentBase
{
public:

	Act3D_JampAttackMoving() = default;

public:

	void start();
	void onEnable();
	void update();

private:

	// ���������ɂ�����u�ԓI�ȗ�
	constexpr static float JumpVerticalPower			{ 4.5f };

	// ���������ɉ��b��ړ����邩�H
	constexpr static float JmupVerticalMoveStartTimeSec	{ 0.1f };

	// ���������ɂ�����p���I�ȗ́i���b�j
	constexpr static float JumpHorizontalSpeedPerSec	{ 5.0f };

	// ���������ɉ��b�Ԉړ����邩�H
	constexpr static float JmupHorizontalMoveTimeSec	{ 1.3f };

private:

	// �����ړ����J�n���鎞�Ԃ�\���^�C�}�[
	float											m_verticalMoveSecTimer		{ 0.0f };

	// �����ړ����s�������ǂ����̃t���O
	bool											m_afterVerticalMove			{ false };

	// �����ړ����s�����Ԃ�\���^�C�}�[
	float											m_horizontalMoveSecTimer	{ 0.0f };

	// ���W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform3D>			m_transform;

	// �����ړ��R���|�[�l���g
	tktk::ComponentPtr<tktk::InertialMovement3D>	m_inertialMovement;
};
#endif // !ACT_3D_JAMP_ATTACK_MOVING_H_