#include "TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h"

namespace tktk
{
	Transform3DMaker Transform3DMaker::m_self;

	Transform3DMaker& Transform3DMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = Transform3DMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<Transform3D> Transform3DMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.empty())
		{
			// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
			return m_user->createComponent<Transform3D>(
				m_initPosition,
				m_initScaleRate,
				m_initRotation,
				m_traceType
				);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<Transform3D>(
			m_initPosition,
			m_initScaleRate,
			m_initRotation,
			m_traceType
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	Transform3DMaker& Transform3DMaker::initPosition(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initPosition = value;
		return *this;
	}

	Transform3DMaker& Transform3DMaker::initScaleRate(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initScaleRate = value;
		return *this;
	}

	Transform3DMaker& Transform3DMaker::initRotation(const tktkMath::Quaternion& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initRotation = value;
		return *this;
	}

	Transform3DMaker& Transform3DMaker::initRotation(const tktkMath::Vector3& value)
	{
		// �N�I�[�^�j�I���ɕϊ������l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initRotation = tktkMath::Quaternion::createFromEulerAngle(value);
		return *this;
	}

	Transform3DMaker& Transform3DMaker::setInitTransformFromMatrix(const tktkMath::Matrix4& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initPosition = value.calculateTranslation();
		m_initScaleRate = value.calculateScale();
		m_initRotation = value.calculateRotation();
		return *this;
	}

	Transform3DMaker& Transform3DMaker::traceType(TraceParentType value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_traceType = value;
		return *this;
	}
}