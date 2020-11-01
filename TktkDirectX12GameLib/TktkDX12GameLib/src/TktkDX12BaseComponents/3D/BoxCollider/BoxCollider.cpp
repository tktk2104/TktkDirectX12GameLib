#include "TktkDX12BaseComponents/3D/BoxCollider/BoxCollider.h"

#include <stdexcept>
#include "TktkDX12BaseComponents/3D/SphereCollider/SphereCollider.h"

namespace tktk
{
	// �����̂̒��_
	constexpr std::array<tktkMath::Vector3, 8U> BoxVert{
		tktkMath::Vector3{ -1.0f, -1.0f, -1.0f }, // 0
		tktkMath::Vector3{  1.0f, -1.0f, -1.0f }, // 1
		tktkMath::Vector3{ -1.0f,  1.0f, -1.0f }, // 2
		tktkMath::Vector3{  1.0f,  1.0f, -1.0f }, // 3
		tktkMath::Vector3{ -1.0f, -1.0f,  1.0f }, // 4
		tktkMath::Vector3{  1.0f, -1.0f,  1.0f }, // 5
		tktkMath::Vector3{ -1.0f,  1.0f,  1.0f }, // 6
		tktkMath::Vector3{  1.0f,  1.0f,  1.0f }  // 7
	};

	BoxCollider::BoxCollider(
		int collisionGroupType,
		const tktkMath::Vector3& boxSize,
		const tktkMath::Vector3& localPosition,
		bool isExtrude,
		float extrudedRate
	)
		: ComponentBase(0.0f, collisionGroupType)
		, m_tempVerts({
			tktkMath::Vector3::scale(BoxVert.at(0U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(2U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(1U), boxSize / 2.0f) + localPosition,
			tktkMath::Vector3::scale(BoxVert.at(1U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(2U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(3U), boxSize / 2.0f) + localPosition,

			tktkMath::Vector3::scale(BoxVert.at(1U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(3U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(5U), boxSize / 2.0f) + localPosition,
			tktkMath::Vector3::scale(BoxVert.at(5U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(3U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(7U), boxSize / 2.0f) + localPosition,

			tktkMath::Vector3::scale(BoxVert.at(5U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(7U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(4U), boxSize / 2.0f) + localPosition,
			tktkMath::Vector3::scale(BoxVert.at(4U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(7U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(6U), boxSize / 2.0f) + localPosition,

			tktkMath::Vector3::scale(BoxVert.at(4U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(6U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(0U), boxSize / 2.0f) + localPosition,
			tktkMath::Vector3::scale(BoxVert.at(0U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(6U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(2U), boxSize / 2.0f) + localPosition,

			tktkMath::Vector3::scale(BoxVert.at(2U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(6U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(3U), boxSize / 2.0f) + localPosition,
			tktkMath::Vector3::scale(BoxVert.at(3U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(6U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(7U), boxSize / 2.0f) + localPosition,

			tktkMath::Vector3::scale(BoxVert.at(0U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(1U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(5U), boxSize / 2.0f) + localPosition,
			tktkMath::Vector3::scale(BoxVert.at(0U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(5U), boxSize / 2.0f) + localPosition, tktkMath::Vector3::scale(BoxVert.at(4U), boxSize / 2.0f) + localPosition
			})
		, m_boundingMesh({
			/* ��O�̖� */
			{ tktkMath::Vector3::scale(BoxVert.at(0U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(2U), boxSize / 2.0f),  tktkMath::Vector3::scale(BoxVert.at(3U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(1U), boxSize / 2.0f)},
			/* �E�̖� */
			{ tktkMath::Vector3::scale(BoxVert.at(1U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(3U), boxSize / 2.0f),  tktkMath::Vector3::scale(BoxVert.at(7U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(5U), boxSize / 2.0f)},
			/* ���̖� */
			{ tktkMath::Vector3::scale(BoxVert.at(5U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(7U), boxSize / 2.0f),  tktkMath::Vector3::scale(BoxVert.at(6U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(4U), boxSize / 2.0f)},
			/* ���̖� */
			{ tktkMath::Vector3::scale(BoxVert.at(4U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(6U), boxSize / 2.0f),  tktkMath::Vector3::scale(BoxVert.at(2U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(0U), boxSize / 2.0f)},
			/* ��̖� */
			{ tktkMath::Vector3::scale(BoxVert.at(2U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(6U), boxSize / 2.0f),  tktkMath::Vector3::scale(BoxVert.at(7U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(3U), boxSize / 2.0f)},
			/* ���̖� */
			{ tktkMath::Vector3::scale(BoxVert.at(0U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(1U), boxSize / 2.0f),  tktkMath::Vector3::scale(BoxVert.at(5U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(4U), boxSize / 2.0f)}
			},
			localPosition)
		, m_isExtrude(isExtrude)
		, m_extrudedRate(extrudedRate)
	{
	}

	void BoxCollider::start()
	{
		m_transform3D = getComponent<Transform3D>();

		if (m_transform3D.expired())
		{
			throw std::runtime_error("RectCollider not found Transform3D");
		}
	}

	bool BoxCollider::isCollide(const ComponentBasePtr& other)
	{
		// �Փˑ���̃R���|�[�l���g���uBoxCollider�v��������
		if (other.canCast<BoxCollider>())
		{
			// �O�������b�V���ƎO�������b�V���ŏՓ˔�����Ă�
			auto otherCollider = other.castPtr<BoxCollider>();
			auto hitInfo = m_boundingMesh.isCollide(otherCollider->getBoundingMesh(), m_transform3D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// �Փˑ�����ƏՓˌ��ʂ����X�g�ɒǉ�����
			m_hitInfo3dPairList.push_front({ other->getGameObject(), otherCollider->isExtrud(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}

		// �Փˑ���̃R���|�[�l���g���uSphereCollider�v��������
		if (other.canCast<SphereCollider>())
		{
			// �O�������b�V���Ƌ��̂ŏՓ˔�����Ă�
			auto otherCollider = other.castPtr<SphereCollider>();
			auto hitInfo = m_boundingMesh.isCollide(otherCollider->getBoundingSphere(), m_transform3D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// �Փˑ�����ƏՓˌ��ʂ����X�g�ɒǉ�����
			m_hitInfo3dPairList.push_front({ other->getGameObject(), otherCollider->isExtrud(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}
		return false;
	}

	void BoxCollider::afterCollide()
	{
		extrusion();

		m_hitInfo3dPairList.clear();
	}

	const tktkCollision::BoundingMesh& BoxCollider::getBoundingMesh() const
	{
		return m_boundingMesh;
	}

	bool BoxCollider::isExtrud() const
	{
		return m_isExtrude;
	}

	float BoxCollider::getExtrudedRate() const
	{
		return m_extrudedRate;
	}

	const ComponentPtr<Transform3D>& BoxCollider::getTransform() const
	{
		return m_transform3D;
	}

	const std::vector<tktkMath::Vector3>& BoxCollider::getTempVerts() const
	{
		return m_tempVerts;
	}

	void BoxCollider::extrusion()
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