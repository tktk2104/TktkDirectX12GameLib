#ifndef ACT_3D_PLAYER_PARAM_H_
#define ACT_3D_PLAYER_PARAM_H_

#include <TktkDX12GameLib.h>

// �v���C���[�̔\�͒l�̃R���|�[�l���g
class Act3D_PlayerParam
	: public tktk::ComponentBase
{
public:

	Act3D_PlayerParam() = default;

public:

	// �����̒l����HP�����炷
	void damage(int damage);

	// HP���[���ȉ������肷��
	bool outOfHp() const;

	// ���݂�HP���擾����
	int getCurHp() const;

public:

	// �ő�HP
	constexpr int getMaxHp() const { return 10; }

private:

	// ���݂�HP
	int m_curHp{ getMaxHp() };
};
#endif // !ACT_3D_PLAYER_PARAM_H_