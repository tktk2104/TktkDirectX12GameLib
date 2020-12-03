#ifndef ACT_3D_END_ATTACK_H_
#define ACT_3D_END_ATTACK_H_

#include <TktkDX12GameLib.h>
#include "../../../../../Enums/Enums.h"

// �v���C���[�̍U���������I������R���|�[�l���g
class Act3D_PlayerEndAttack
	: public tktk::ComponentBase
{
public:

	explicit Act3D_PlayerEndAttack(float endAttackTime);

public:

	void onEnable();
	void update();

private:

	// �U�����I������܂ł̎���
	const float				m_endAttackTimeSec;

	// �U�����I�����邽�߂̃^�C�}�[
	float					m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_END_ATTACK_H_