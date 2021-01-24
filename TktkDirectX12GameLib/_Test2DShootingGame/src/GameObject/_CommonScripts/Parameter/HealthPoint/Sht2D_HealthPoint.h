#ifndef SHT_2D_HEALTH_POINT_H_
#define SHT_2D_HEALTH_POINT_H_

#include <TktkDX12GameLib.h>

class Sht2D_HealthPoint
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_HealthPoint(float maxHp);

public:

	// �����̒l����HP�����炷
	void damage(float damage);

	// HP���[���ȉ������肷��
	bool outOfHp() const;

	// ���݂�HP���擾����
	float getCurHp() const;

	// �ő��HP���擾����
	float getMaxHp() const;

private:

	float m_maxHp;

	float m_curHp;
};
#endif // !SHT_2D_HEALTH_POINT_H_