#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BoxMeshShadowMapWriterMaker.h"

namespace tktk
{
	BoxMeshShadowMapWriterMaker BoxMeshShadowMapWriterMaker::m_self;

	BoxMeshShadowMapWriterMaker& BoxMeshShadowMapWriterMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BoxMeshShadowMapWriterMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p����J�����n���h���̃f�t�H���g�l�̓f�t�H���g�V���h�E�}�b�v�J����
		m_self.m_cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<BoxMeshShadowMapWriter> BoxMeshShadowMapWriterMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<BoxMeshShadowMapWriter>(
			m_drawPriority,
			m_boxSize,
			m_localPosition,
			m_cameraHandle
			);
	}

	BoxMeshShadowMapWriterMaker& BoxMeshShadowMapWriterMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	BoxMeshShadowMapWriterMaker& BoxMeshShadowMapWriterMaker::boxSize(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_boxSize = value;
		return *this;
	}

	BoxMeshShadowMapWriterMaker& BoxMeshShadowMapWriterMaker::localPosition(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_localPosition = value;
		return *this;
	}

	BoxMeshShadowMapWriterMaker& BoxMeshShadowMapWriterMaker::cameraIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}
}