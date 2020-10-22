#include "TktkDX12BaseComponents/2D/Polygon2dCollider/Polygon2dCollider.h"

#include <vector>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include "TktkDX12BaseComponents/2D/RectCollider/RectCollider.h"
#include "TktkDX12BaseComponents/2D/CircleCollider/CircleCollider.h"

namespace tktk
{
	Polygon2dCollider::Polygon2dCollider(
		int collisionGroupType,
		const std::vector<tktkMath::Vector2>& vertexs,
		float extrudedRate
	)
		: ComponentBase(0.0f, collisionGroupType)
		, m_boundingPolygon2d(vertexs)
		, m_extrudedRate(extrudedRate)
	{
	}

	void Polygon2dCollider::start()
	{
		m_transform2D = getComponent<Transform2D>();

		if (m_transform2D.expired())
		{
			throw std::runtime_error("RectCollider not found Transform2D");
		}
	}

	bool Polygon2dCollider::isCollide(const ComponentBasePtr& other)
	{
		// �Փˑ���̃R���|�[�l���g���uRectCollider�v��������
		if (other.canCast<RectCollider>())
		{
			// �񎟌��|���S���Ɠ񎟌��|���S���ŏՓ˔�����Ă�
			auto otherCollider = other.castPtr<RectCollider>();
			auto hitInfo = m_boundingPolygon2d.isCollide(otherCollider->getBoundingPolygon2d(), m_transform2D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// �Փˑ�����ƏՓˌ��ʂ����X�g�ɒǉ�����
			m_hitInfo2dPairList.push_front({ other->getGameObject(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}

		// �Փˑ���̃R���|�[�l���g���uCircleCollider�v��������
		if (other.canCast<CircleCollider>())
		{
			// �񎟌��|���S���Ɖ~�ŏՓ˔�����Ă�
			auto otherCollider = other.castPtr<CircleCollider>();
			auto hitInfo = m_boundingPolygon2d.isCollide(otherCollider->getBoundingCircle(), m_transform2D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// �Փˑ�����ƏՓˌ��ʂ����X�g�ɒǉ�����
			m_hitInfo2dPairList.push_front({ other->getGameObject(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}

		// �Փˑ���̃R���|�[�l���g���uPolygon2dCollider�v��������
		if (other.canCast<Polygon2dCollider>())
		{
			// �񎟌��|���S���Ɠ񎟌��|���S���ŏՓ˔�����Ă�
			auto otherCollider = other.castPtr<Polygon2dCollider>();
			auto hitInfo = m_boundingPolygon2d.isCollide(otherCollider->getBoundingPolygon2d(), m_transform2D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// �Փˑ�����ƏՓˌ��ʂ����X�g�ɒǉ�����
			m_hitInfo2dPairList.push_front({ other->getGameObject(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}
		return false;
	}

	void Polygon2dCollider::afterCollide()
	{
		extrusion();

		m_hitInfo2dPairList.clear();
	}

	const tktkCollision::BoundingPolygon2D& Polygon2dCollider::getBoundingPolygon2d() const
	{
		return m_boundingPolygon2d;
	}

	float Polygon2dCollider::getExtrudedRate() const
	{
		return m_extrudedRate;
	}

	const ComponentPtr<Transform2D>& Polygon2dCollider::getTransform() const
	{
		return m_transform2D;
	}

	void Polygon2dCollider::extrusion()
	{
		for (const auto& node : m_hitInfo2dPairList)
		{
			// �����o����₷���̍��v�����߂�
			float sumExtrudedRate = m_extrudedRate + node.otherExtrudedRate;

			// �[���Ŋ��낤�Ƃ�����ً}���
			if (sumExtrudedRate == 0.0f) continue;

			// ���g�̉����o���������s��
			m_transform2D->addWorldPosition(node.hitInfo.selfExtrudeVec * (m_extrudedRate / sumExtrudedRate));

			// ����̍��W�Ǘ��R���|�[�l���g���擾
			auto otherTransform = node.otherObject->getComponent<tktk::Transform2D>();

			// ����̉����o���������s��
			otherTransform->addWorldPosition(-node.hitInfo.selfExtrudeVec * (node.otherExtrudedRate / sumExtrudedRate));
		}
	}
}