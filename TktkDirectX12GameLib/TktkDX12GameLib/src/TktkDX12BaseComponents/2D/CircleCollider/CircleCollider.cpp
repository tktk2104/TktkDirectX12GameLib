#include "TktkDX12BaseComponents/2D/CircleCollider/CircleCollider.h"

#include <stdexcept>
#include "TktkDX12BaseComponents/2D/Transform2D/Transform2D.h"
#include "TktkDX12BaseComponents/2D/RectCollider/RectCollider.h"
#include "TktkDX12BaseComponents/2D/Polygon2dCollider/Polygon2dCollider.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	CircleCollider::CircleCollider(
		CollisionGroupTypeCarrier collisionGroupType,
		float radius,
		const tktkMath::Vector2 & localPosition,
		bool isExtrude,
		float extrudedRate
	)
		: ComponentBase(0.0f, collisionGroupType)
		, m_boundingCircle(radius, localPosition)
		, m_isExtrude(isExtrude)
		, m_extrudedRate(extrudedRate)
	{
	}

	void CircleCollider::start()
	{
		m_transform2D = getComponent<Transform2D>();

		if (m_transform2D.expired())
		{
			throw std::runtime_error("CircleCollider not found Transform2D");
		}
	}

	bool CircleCollider::isCollide(const ComponentBasePtr& other)
	{
		// �Փˑ���̃R���|�[�l���g���uRectCollider�v��������
		if (other.canCast<RectCollider>())
		{
			// �~�Ɠ񎟌��|���S���̏Փ˔�����Ă�
			auto otherCollider = other.castPtr<RectCollider>();
			auto hitInfo = m_boundingCircle.isCollide(otherCollider->getBoundingPolygon2d(), m_transform2D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// �Փˑ�����ƏՓˌ��ʂ����X�g�ɒǉ�����
			m_hitInfo2dPairList.push_front({ other->getGameObject(), otherCollider->isExtrud(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}

		// �Փˑ���̃R���|�[�l���g���uCircleCollider�v��������
		if (other.canCast<CircleCollider>())
		{
			// �~�Ɖ~�ŏՓ˔�����Ă�
			auto otherCollider = other.castPtr<CircleCollider>();
			auto hitInfo = m_boundingCircle.isCollide(otherCollider->getBoundingCircle(), m_transform2D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// �Փˑ�����ƏՓˌ��ʂ����X�g�ɒǉ�����
			m_hitInfo2dPairList.push_front({ other->getGameObject(), otherCollider->isExtrud(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}

		// �Փˑ���̃R���|�[�l���g���uPolygon2dCollider�v��������
		if (other.canCast<Polygon2dCollider>())
		{
			// �~�Ɠ񎟌��|���S���̏Փ˔�����Ă�
			auto otherCollider = other.castPtr<Polygon2dCollider>();
			auto hitInfo = m_boundingCircle.isCollide(otherCollider->getBoundingPolygon2d(), m_transform2D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// �Փˑ�����ƏՓˌ��ʂ����X�g�ɒǉ�����
			m_hitInfo2dPairList.push_front({ other->getGameObject(), otherCollider->isExtrud(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}
		return false;
	}

	void CircleCollider::afterCollide()
	{
		extrusion();

		m_hitInfo2dPairList.clear();
	}

	const tktkCollision::BoundingCircle& CircleCollider::getBoundingCircle() const
	{
		return m_boundingCircle;
	}

	bool CircleCollider::isExtrud() const
	{
		return m_isExtrude;
	}

	float CircleCollider::getExtrudedRate() const
	{
		return m_extrudedRate;
	}

	const ComponentPtr<Transform2D>& CircleCollider::getTransform() const
	{
		return m_transform2D;
	}

	void CircleCollider::extrusion()
	{
		for (const auto& node : m_hitInfo2dPairList)
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
			m_transform2D->addWorldPosition(node.hitInfo.selfExtrudeVec * (selfExtrudedRate / sumExtrudedRate));

			// ����̍��W�Ǘ��R���|�[�l���g���擾
			auto otherTransform = node.otherObject->getComponent<tktk::Transform2D>();

			// ����̉����o���������s��
			otherTransform->addWorldPosition(-node.hitInfo.selfExtrudeVec * (otherExtrudedRate / sumExtrudedRate));
		}
	}
}