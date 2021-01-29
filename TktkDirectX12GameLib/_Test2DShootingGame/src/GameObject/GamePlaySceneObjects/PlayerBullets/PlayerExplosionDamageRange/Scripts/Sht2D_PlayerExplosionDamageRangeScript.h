#ifndef SHT_2D_PLAYER_EXPLOSION_DAMAGE_RANGE_SCRIPT_H_
#define SHT_2D_PLAYER_EXPLOSION_DAMAGE_RANGE_SCRIPT_H_

#include <TktkDX12GameLib.h>

// ��莞�Ԍ�Ɏ��g���E���R���|�[�l���g
class Sht2D_PlayerExplosionDamageRangeScript
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_PlayerExplosionDamageRangeScript(float deadTimeSec);
	~Sht2D_PlayerExplosionDamageRangeScript() = default;

public:

	// ���t���[���Ă΂��
	void update();

private:

	// �U���͈͏��Ń^�C�}�[�i�b�j
	float m_deadSecTimer;
};
#endif // !SHT_2D_PLAYER_EXPLOSION_DAMAGE_RANGE_SCRIPT_H_