#ifndef SHT_2D_AUTO_ROTATER_H_
#define SHT_2D_AUTO_ROTATER_H_

#include <TktkDX12GameLib.h>

// ������]�R���|�[�l���g
class Sht2D_AutoRotater
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_AutoRotater(float rotateSpeedPerSecDeg);

public:

	void start();
	void update();

private:

	// ���b�̉�]�p�x�i�x���@�j
	float m_rotateSpeedPerSecDeg;

	tktk::ComponentPtr<tktk::Transform2D>			m_transform;
};
#endif // !SHT_2D_AUTO_ROTATER_H_
