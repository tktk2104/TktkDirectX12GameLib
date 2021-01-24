#ifndef SHT_2D_ROTETE_TO_OBJECT_H_
#define SHT_2D_ROTETE_TO_OBJECT_H_

#include <TktkDX12GameLib.h>

// �w��̃I�u�W�F�N�g�����ɉ�]����R���|�[�l���g
class Sht2D_RoteteToObject
	: public tktk::ComponentBase
{
public:

	Sht2D_RoteteToObject(
		float rotateSpeedPerSecDeg,
		const tktk::GameObjectPtr& rotateTarget
	);

public:

	void start();
	void update();

private:

	float				m_rotateSpeedPerSecDeg;

	tktk::ComponentPtr<tktk::Transform2D>			m_roteteTargetTransform;

	tktk::ComponentPtr<tktk::Transform2D>			m_transform;
};
#endif // !SHT_2D_ROTETE_TO_OBJECT_H_
