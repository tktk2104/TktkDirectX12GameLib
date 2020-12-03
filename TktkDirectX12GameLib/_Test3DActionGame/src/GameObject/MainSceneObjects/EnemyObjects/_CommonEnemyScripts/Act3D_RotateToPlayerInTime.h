#ifndef ACT_3D_ROTATE_TO_PLAYER_IN_TIME_H_
#define ACT_3D_ROTATE_TO_PLAYER_IN_TIME_H_

#include <TktkDX12GameLib.h>

// ��莞�Ԃ̊ԃv���C���[�̕����։�]���鏈�����s���R���|�[�l���g
class Act3D_RotateToPlayerInTime
	: public tktk::ComponentBase
{
public:

	Act3D_RotateToPlayerInTime(float roteteSpeedPerSecDeg, float rotateEndTimeSec);

public:

	void start();
	void onEnable();
	void update();

private:

	// ���b�̉�]�p�x�i�x���@�j
	const float	m_roteteSpeedPerSecDeg;

	// ��]���I������܂ł̎���
	const float	m_rotateEndTimeSec;

	// ��]���I�����鏈�����s�����߂̃^�C�}�[
	float		m_rotateEndSecTimer{ 0.0f };
	
	// ���g�̍��W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;

	// �v���C���[�̍��W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_ROTATE_TO_PLAYER_IN_TIME_H_