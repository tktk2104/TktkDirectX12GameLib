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
		// 衝突相手のコンポーネントが「RectCollider」だったら
		if (other.canCast<RectCollider>())
		{
			// 円と二次元ポリゴンの衝突判定を呼ぶ
			auto otherCollider = other.castPtr<RectCollider>();
			auto hitInfo = m_boundingCircle.isCollide(otherCollider->getBoundingPolygon2d(), m_transform2D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// 衝突相手情報と衝突結果をリストに追加する
			m_hitInfo2dPairList.push_front({ other->getGameObject(), otherCollider->isExtrud(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}

		// 衝突相手のコンポーネントが「CircleCollider」だったら
		if (other.canCast<CircleCollider>())
		{
			// 円と円で衝突判定を呼ぶ
			auto otherCollider = other.castPtr<CircleCollider>();
			auto hitInfo = m_boundingCircle.isCollide(otherCollider->getBoundingCircle(), m_transform2D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// 衝突相手情報と衝突結果をリストに追加する
			m_hitInfo2dPairList.push_front({ other->getGameObject(), otherCollider->isExtrud(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}

		// 衝突相手のコンポーネントが「Polygon2dCollider」だったら
		if (other.canCast<Polygon2dCollider>())
		{
			// 円と二次元ポリゴンの衝突判定を呼ぶ
			auto otherCollider = other.castPtr<Polygon2dCollider>();
			auto hitInfo = m_boundingCircle.isCollide(otherCollider->getBoundingPolygon2d(), m_transform2D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// 衝突相手情報と衝突結果をリストに追加する
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
			// 相手が自身を押し出そうとしていたら、自身の押し出されやすさを適応する
			float selfExtrudedRate = (node.isExtrude) ? m_extrudedRate : 0.0f;

			// 相手を押し出す設定の場合、相手の押し出されやすさを適応する
			float otherExtrudedRate = (m_isExtrude) ? node.otherExtrudedRate : 0.0f;

			// 押し出されやすさの合計を求める
			float sumExtrudedRate = selfExtrudedRate + otherExtrudedRate;

			// ゼロで割ろうとしたら緊急回避
			if (sumExtrudedRate == 0.0f) continue;

			// 自身の押し出し処理を行う
			m_transform2D->addWorldPosition(node.hitInfo.selfExtrudeVec * (selfExtrudedRate / sumExtrudedRate));

			// 相手の座標管理コンポーネントを取得
			auto otherTransform = node.otherObject->getComponent<tktk::Transform2D>();

			// 相手の押し出し処理を行う
			otherTransform->addWorldPosition(-node.hitInfo.selfExtrudeVec * (otherExtrudedRate / sumExtrudedRate));
		}
	}
}