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

	// ���b�̍ő��]�p�x�i�x���@�j
	float				m_rotateSpeedPerSecDeg;

	// ��]�Ώۂ̍��W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform2D>			m_roteteTargetTransform;

	// ���g�̍��W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform2D>			m_transform;
};
#endif // !SHT_2D_ROTETE_TO_OBJECT_H_
