#ifndef SHT_2D_AUTO_ROTATER_H_
#define SHT_2D_AUTO_ROTATER_H_

#include <TktkDX12GameLib.h>

// 自動回転コンポーネント
class Sht2D_AutoRotater
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_AutoRotater(float rotateSpeedPerSecDeg);

public:

	void start();
	void update();

private:

	// 毎秒の回転角度（度数法）
	float m_rotateSpeedPerSecDeg;

	tktk::ComponentPtr<tktk::Transform2D>			m_transform;
};
#endif // !SHT_2D_AUTO_ROTATER_H_
