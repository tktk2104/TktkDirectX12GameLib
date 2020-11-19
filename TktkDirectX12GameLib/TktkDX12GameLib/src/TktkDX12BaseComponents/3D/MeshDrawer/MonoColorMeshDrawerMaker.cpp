#include "TktkDX12BaseComponents/3D/MeshDrawer/MonoColorMeshDrawerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	MonoColorMeshDrawerMaker MonoColorMeshDrawerMaker::m_self;

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = MonoColorMeshDrawerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<MonoColorMeshDrawer> MonoColorMeshDrawerMaker::create()
	{
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<MonoColorMeshDrawer>(m_meshHandle, m_skeletonHandle, m_albedoColor, m_basePosition, m_baseScale, m_baseRotation);
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::setBoxMesh()
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_meshHandle = DX12GameManager::getSystemHandle(SystemMeshType::Box);
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::setBoxMeshWireFrame()
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_meshHandle = DX12GameManager::getSystemHandle(SystemMeshType::BoxWireFrame);
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::setSphereMesh()
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_meshHandle = DX12GameManager::getSystemHandle(SystemMeshType::Sphere);
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::setSphereMeshWireFrame()
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_meshHandle = DX12GameManager::getSystemHandle(SystemMeshType::SphereWireFrame);
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::meshHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_meshHandle = value;
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::meshId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_meshHandle = DX12GameManager::getBasicMeshHandle(value);
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::skeletonHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_skeletonHandle = value;
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::skeletonId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_skeletonHandle = DX12GameManager::getSkeletonHandle(value);
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::albedoColor(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_albedoColor = value;
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::basePosition(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_basePosition = value;
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::baseScale(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_baseScale = value;
		return *this;
	}

	MonoColorMeshDrawerMaker& MonoColorMeshDrawerMaker::baseRotation(const tktkMath::Quaternion& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_baseRotation = value;
		return *this;
	}
}