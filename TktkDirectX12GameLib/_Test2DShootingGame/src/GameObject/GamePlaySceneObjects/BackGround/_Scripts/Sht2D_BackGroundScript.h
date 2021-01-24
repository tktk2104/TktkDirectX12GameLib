#ifndef SHT_2D_BACK_GROUND_SCRIPT_H_
#define SHT_2D_BACK_GROUND_SCRIPT_H_

#include <TktkDX12GameLib.h>

class Sht2D_BackGroundScript
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_BackGroundScript(const tktkMath::Vector2& velocityPerSec);

public:

	void start();
	void update();

private:

	tktkMath::Vector2 m_velocityPerSec;

	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !SHT_2D_BACK_GROUND_SCRIPT_H_