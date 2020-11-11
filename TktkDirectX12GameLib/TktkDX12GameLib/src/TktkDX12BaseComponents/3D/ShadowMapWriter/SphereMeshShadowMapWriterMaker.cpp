#include "TktkDX12BaseComponents/3D/ShadowMapWriter/SphereMeshShadowMapWriterMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	SphereMeshShadowMapWriterMaker SphereMeshShadowMapWriterMaker::m_self;

	SphereMeshShadowMapWriterMaker& SphereMeshShadowMapWriterMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = SphereMeshShadowMapWriterMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p����J�����n���h���̃f�t�H���g�l�̓f�t�H���g�V���h�E�}�b�v�J����
		m_self.m_cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<SphereMeshShadowMapWriter> SphereMeshShadowMapWriterMaker::create()
	{
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<SphereMeshShadowMapWriter>(
			m_drawPriority,
			m_radius,
			m_localPosition,
			m_cameraHandle
			);
	}

	SphereMeshShadowMapWriterMaker& SphereMeshShadowMapWriterMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	SphereMeshShadowMapWriterMaker& SphereMeshShadowMapWriterMaker::radius(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_radius = value;
		return *this;
	}

	SphereMeshShadowMapWriterMaker& SphereMeshShadowMapWriterMaker::localPosition(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_localPosition = value;
		return *this;
	}

	SphereMeshShadowMapWriterMaker& SphereMeshShadowMapWriterMaker::cameraId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}
}