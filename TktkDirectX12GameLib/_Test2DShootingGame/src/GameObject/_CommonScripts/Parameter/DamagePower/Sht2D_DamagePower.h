#ifndef SHT_2D_DAMAGE_POWER_H_
#define SHT_2D_DAMAGE_POWER_H_

#include <TktkDX12GameLib.h>

// �ڐG���̃_���[�W�p���[�R���|�[�l���g
class Sht2D_DamagePower
	: public tktk::ComponentBase
{
public:

	Sht2D_DamagePower(float startHitPower, float stayHitPowerPerSec);

public:

	// �ڐG�J�n���_���[�W���擾����
	float getStartHitPower() const;

	// ���b�̐ڐG���_���[�W���擾����
	float getStayHitPowerPerSec() const;

private:

	// �ڐG�J�n���_���[�W
	float m_startHitPower;

	// �ڐG���_���[�W�i���b�j
	float m_stayHitPowerPerSec;
};
#endif // !SHT_2D_DAMAGE_POWER_H_