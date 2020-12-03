#ifndef ACT_3D_ROTATE_TO_PLAYER_H_
#define ACT_3D_ROTATE_TO_PLAYER_H_

#include <TktkDX12GameLib.h>

// �v���C���[�̕��։�]���鏈�����s���R���|�[�l���g
class Act3D_RotateToPlayer
	: public tktk::ComponentBase
{
public:

	explicit Act3D_RotateToPlayer(float roteteSpeedPerSecDeg);

public:

	void start();
	void update();

private:

	// ���b�̉�]�p�x�i�x���@�j
	float									m_roteteSpeedPerSecDeg;

	// ���g�̍��W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;

	// �v���C���[�̍��W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_ROTATE_TO_PLAYER_H_