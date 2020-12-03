#include "TktkDX12BaseComponents/3D/MeshDrawer/MeshDrawerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	MeshDrawerMaker MeshDrawerMaker::m_self;

	MeshDrawerMaker& MeshDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = MeshDrawerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<MeshDrawer> MeshDrawerMaker::create()
	{
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<MeshDrawer>(m_meshHandle, m_skeletonHandle, m_basePosition, m_baseScale, m_baseRotation);
	}

	MeshDrawerMaker& MeshDrawerMaker::meshHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_meshHandle = value;
		return *this;
	}

	MeshDrawerMaker& MeshDrawerMaker::meshId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_meshHandle = DX12GameManager::getBasicMeshHandle(value);
		return *this;
	}

	MeshDrawerMaker& MeshDrawerMaker::skeletonHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_skeletonHandle = value;
		return *this;
	}

	MeshDrawerMaker& MeshDrawerMaker::skeletonId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_skeletonHandle = DX12GameManager::getSkeletonHandle(value);
		return *this;
	}

	MeshDrawerMaker& MeshDrawerMaker::basePosition(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_basePosition = value;
		return *this;
	}

	MeshDrawerMaker& MeshDrawerMaker::baseScale(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_baseScale = value;
		return *this;
	}

	MeshDrawerMaker& MeshDrawerMaker::baseRotation(const tktkMath::Quaternion& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_baseRotation = value;
		return *this;
	}
}