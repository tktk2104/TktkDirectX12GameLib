#ifndef ACT_3D_PLAYER_END_DODGE_H_
#define ACT_3D_PLAYER_END_DODGE_H_

#include <TktkDX12GameLib.h>

// �v���C���[�̉����Ԃ��I������R���|�[�l���g
class Act3D_PlayerEndDodge
	: public tktk::ComponentBase
{
public:

	void start();
	void onEnable();
	void update();

private:

	// �����Ԃ��I���܂ł̎���
	static constexpr float EndDodgeTimeSec{ 1.0f };

private:

	// �����Ԃ��I�����邽�߂̃^�C�}�[
	float m_endDodgeSecTimer{ 0.0f };

	// ���b�V���`��R���|�[�l���g
	tktk::ComponentPtr<tktk::MeshDrawer>	m_meshDrawer;
};
#endif // !ACT_3D_PLAYER_END_DODGE_H_