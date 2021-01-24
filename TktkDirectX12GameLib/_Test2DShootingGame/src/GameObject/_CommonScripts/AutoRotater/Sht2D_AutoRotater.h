#ifndef SHT_2D_AUTO_ROTATER_H_
#define SHT_2D_AUTO_ROTATER_H_

#include <TktkDX12GameLib.h>

class Sht2D_AutoRotater
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_AutoRotater(float rotateSpeedPerSec);

public:

	void start();
	void update();

private:

	float m_rotateSpeedPerSec;

	tktk::ComponentPtr<tktk::Transform2D>			m_transform;
};
#endif // !SHT_2D_AUTO_ROTATER_H_
