#include "TktkDX12BaseComponents/3D/SphereCollider/SphereCollider.h"

#include <stdexcept>
#include "TktkDX12BaseComponents/3D/BoxCollider/BoxCollider.h"

namespace tktk
{
	SphereCollider::SphereCollider(
		int collisionGroupType,
		float radius,
		const tktkMath::Vector3& localPosition,
		bool isExtrude,
		float extrudedRate
	)
		: ComponentBase(0.0f, collisionGroupType)
		, m_boundingSphere(radius, localPosition)
		, m_isExtrude(isExtrude)
		, m_extrudedRate(extrudedRate)
	{
	}

	void SphereCollider::start()
	{
		m_transform3D = getComponent<Transform3D>();

		if (m_transform3D.expired())
		{
			throw std::runtime_error("RectCollider not found Transform3D");
		}
	}

	bool SphereCollider::isCollide(const ComponentBasePtr& other)
	{
		// �Փˑ���̃R���|�[�l���g���uBoxCollider�v��������
		if (other.canCast<BoxCollider>())
		{
			// ���̂ƎO�������b�V���ŏՓ˔�����Ă�
			auto otherCollider = other.castPtr<BoxCollider>();
			auto hitInfo = m_boundingSphere.isCollide(otherCollider->getBoundingMesh(), m_transform3D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// �Փˑ�����ƏՓˌ��ʂ����X�g�ɒǉ�����
			m_hitInfo3dPairList.push_front({ other->getGameObject(), otherCollider->isExtrud(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}

		// �Փˑ���̃R���|�[�l���g���uSphereCollider�v��������
		if (other.canCast<SphereCollider>())
		{
			// ���̂Ƌ��̂ŏՓ˔�����Ă�
			auto otherCollider = other.castPtr<SphereCollider>();
			auto hitInfo = m_boundingSphere.isCollide(otherCollider->getBoundingSphere(), m_transform3D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// �Փˑ�����ƏՓˌ��ʂ����X�g�ɒǉ�����
			m_hitInfo3dPairList.push_front({ other->getGameObject(), otherCollider->isExtrud(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}
		return false;
	}

	void SphereCollider::afterCollide()
	{
		extrusion();

		m_hitInfo3dPairList.clear();
	}

	const tktkCollision::BoundingSphere& SphereCollider::getBoundingSphere() const
	{
		return m_boundingSphere;
	}

	bool SphereCollider::isExtrud() const
	{
		return m_isExtrude;
	}

	float SphereCollider::getExtrudedRate() const
	{
		return m_extrudedRate;
	}

	const ComponentPtr<Transform3D>& SphereCollider::getTransform() const
	{
		return m_transform3D;
	}

	void SphereCollider::extrusion()
	{
		for (const auto& node : m_hitInfo3dPairList)
		{
			// ���肪���g�������o�����Ƃ��Ă�����A���g�̉����o����₷����K������
			float selfExtrudedRate = (node.isExtrude) ? m_extrudedRate : 0.0f;

			// ����������o���ݒ�̏ꍇ�A����̉����o����₷����K������
			float otherExtrudedRate = (m_isExtrude) ? node.otherExtrudedRate : 0.0f;

			// �����o����₷���̍��v�����߂�
			float sumExtrudedRate = selfExtrudedRate + otherExtrudedRate;

			// �[���Ŋ��낤�Ƃ�����ً}���
			if (sumExtrudedRate == 0.0f) continue;

			// ���g�̉����o���������s��
			m_transform3D->addWorldPosition(node.hitInfo.selfExtrudeVec * (selfExtrudedRate / sumExtrudedRate));

			// ����̍��W�Ǘ��R���|�[�l���g���擾
			auto otherTransform = node.otherObject->getComponent<tktk::Transform3D>();

			// ����̉����o���������s��
			otherTransform->addWorldPosition(-node.hitInfo.selfExtrudeVec * (otherExtrudedRate / sumExtrudedRate));
		}
	}
}