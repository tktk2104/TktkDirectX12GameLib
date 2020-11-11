#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BasicMeshShadowMapWriterMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	BasicMeshShadowMapWriterMaker BasicMeshShadowMapWriterMaker::m_self;

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BasicMeshShadowMapWriterMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p����J�����n���h���̃f�t�H���g�l�̓f�t�H���g�V���h�E�}�b�v�J����
		m_self.m_cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<BasicMeshShadowMapWriter> BasicMeshShadowMapWriterMaker::create()
	{
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<BasicMeshShadowMapWriter>(
			m_drawPriority,
			m_baseScale,
			m_baseRotation,
			m_meshHandle,
			m_skeletonHandle,
			m_cameraHandle
			);
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::baseScale(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_baseScale = value;
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::baseRotation(const tktkMath::Quaternion& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_baseRotation = value;
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::meshId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_meshHandle = DX12GameManager::getBasicMeshHandle(value);
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::skeletonId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_skeletonHandle = DX12GameManager::getSkeletonHandle(value);
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::cameraId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}
}