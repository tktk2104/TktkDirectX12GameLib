#ifndef INERTIAL_MOVEMENT_3D_H_
#define INERTIAL_MOVEMENT_3D_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	/* class member */
	class Transform3D;

	// �R���������ړ��R���|�[�l���g
	class InertialMovement3D
		: public ComponentBase
	{
	public:

		InertialMovement3D(
			float decelerationPerSec,		// ���x���P�b�Ԃłǂꂾ�����������邩�H
			const tktkMath::Vector3 & initVelocity	// �������x
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();

	public:

		// �u�ԓI�ɗ͂�������i�����̃x�N�g�������̂܂ܑ��x�ɉ�����j
		void addMomentarilyForce(const tktkMath::Vector3& force);

		// �p���I�ɗ͂�������i�������̃x�N�g����ڎw���āA���b�������̒����̃x�N�g���𑬓x�ɉ�����j
		// �����t���[���Ă�ł�������
		// �����������[���x�N�g���������ꍇ�͉������܂���
		void addContinuousForce(const tktkMath::Vector3& force, float accelerationPerSec);

		// ���݂̑��x���擾
		tktkMath::Vector3 getVelocity() const;

		// ���݂̑��x��ݒ�
		void setVelocity(const tktkMath::Vector3& velocity);

	private:

		// ���g�̂R�������W�R���|�[�l���g
		ComponentPtr<Transform3D> m_transform3D;

		// ���x
		tktkMath::Vector3 m_velocity;

		// ���x���P�b�Ԃłǂꂾ�����������邩�H
		float m_decelerationPerSec;
	};
}
#endif // !INERTIAL_MOVEMENT_3D_H_