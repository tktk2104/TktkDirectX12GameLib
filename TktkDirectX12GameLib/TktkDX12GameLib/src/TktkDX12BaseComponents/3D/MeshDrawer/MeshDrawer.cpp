#include "TktkDX12BaseComponents/3D/MeshDrawer/MeshDrawer.h"

#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"
#include "TktkDX12BaseComponents/3D/MeshAnimator/MeshAnimator.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	MeshDrawer::MeshDrawer(size_t meshHandle, size_t skeletonHandle, const tktkMath::Vector3& basePosition, const tktkMath::Vector3& baseScale, const tktkMath::Quaternion& baseRotation)
		: m_meshHandle(meshHandle)
		, m_skeletonHandle(skeletonHandle)
		, m_basePosition(basePosition)
		, m_baseScale(baseScale)
		, m_baseRotation(baseRotation)
	{
	}

	void MeshDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}

		m_animator = getComponent<MeshAnimator>();
	}

	void MeshDrawer::afterCollide()
	{
		if (!m_animator.expired() && m_skeletonHandle != 0U) m_animator->transformSkeleton(m_skeletonHandle);

		// ���[���h�s��
		auto worldMatrix = tktkMath::Matrix4::createTRS(
			m_basePosition + m_transform->getWorldPosition(),
			m_baseRotation * m_transform->getWorldRotation(),
			tktkMath::Vector3::scale(m_baseScale, m_transform->getWorldScaleRate())
		);

		// �w��̃��b�V�����C���X�^���X�`�悷�鎞�Ɏg�p����l��ǉ�����
		DX12GameManager::addMeshInstanceVertParam(m_meshHandle, worldMatrix);

		// �����X�P���g�����ݒ肳��Ă�����
		if (m_skeletonHandle != 0U)
		{
			// �w��̃X�L�j���O���b�V�����C���X�^���X�`�悷�鎞�Ɏg�p���鍜�s���ǉ�����
			DX12GameManager::addMeshInstanceBoneMatrix(m_meshHandle, m_skeletonHandle);
		}
	}

	const tktkMath::Vector3& MeshDrawer::getBasePosition() const
	{
		return m_basePosition;
	}

	void MeshDrawer::setBasePosition(const tktkMath::Vector3& position)
	{
		m_basePosition = position;
	}

	const tktkMath::Vector3& MeshDrawer::getBaseScale() const
	{
		return m_baseScale;
	}

	void MeshDrawer::setBaseScale(const tktkMath::Vector3& scale)
	{
		m_baseScale = scale;
	}

	const tktkMath::Quaternion& MeshDrawer::getBaseRotation() const
	{
		return m_baseRotation;
	}

	void MeshDrawer::setBaseRotation(const tktkMath::Quaternion& rotation)
	{
		m_baseRotation = rotation;
	}
}