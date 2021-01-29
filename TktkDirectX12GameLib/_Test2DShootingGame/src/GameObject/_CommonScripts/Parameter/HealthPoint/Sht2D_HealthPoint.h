#ifndef SHT_2D_HEALTH_POINT_H_
#define SHT_2D_HEALTH_POINT_H_

#include <TktkDX12GameLib.h>

// �ϋv�͂̃R���|�[�l���g
class Sht2D_HealthPoint
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_HealthPoint(float maxHp);

public:

	// �����̒l�����ϋv�͂����炷
	void damage(float damage);

	// �ϋv�͂��[���ȉ������肷��
	bool outOfHp() const;

	// ���݂̑ϋv�͂��擾����
	float getCurHp() const;

	// �ő�̑ϋv�͂��擾����
	float getMaxHp() const;

private:

	// �ő�ϋv��
	float m_maxHp;

	// ���݂̑ϋv��
	float m_curHp;
};
#endif // !SHT_2D_HEALTH_POINT_H_