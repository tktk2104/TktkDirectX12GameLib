#ifndef ACT_3D_INPUT_TO_START_DODGE_H_
#define ACT_3D_INPUT_TO_START_DODGE_H_

#include <TktkDX12GameLib.h>

// ���͂ɂ���ĉ���s�����J�n����R���|�[�l���g
class Act3D_InputToStartDodge
	: public tktk::ComponentBase
{
public:

	Act3D_InputToStartDodge() = default;

public:

	void start();
	void update();

private:

	// ����̃C���^�[�o��
	constexpr static float DodgeIntervalTimeSec{ 0.7f };

	// ����ړ��̏���
	constexpr static float DodgeMovePower{ 6.0f };

private:

	// ����Ԋu���Ǘ�����^�C�}�[
	float m_dodgeIntervelSecTimer{ 0.0f };

	// ���b�V���`��R���|�[�l���g
	tktk::ComponentPtr<tktk::MeshDrawer>			m_meshDrawer;

	// ���W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform3D>			m_transform;

	// �����ړ��R���|�[�l���g
	tktk::ComponentPtr<tktk::InertialMovement3D>	m_inertialMovement;
};
#endif // !ACT_3D_INPUT_TO_START_DODGE_H_