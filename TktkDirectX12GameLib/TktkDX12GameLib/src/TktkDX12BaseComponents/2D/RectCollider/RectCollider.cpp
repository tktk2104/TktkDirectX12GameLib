#include "TktkDX12BaseComponents/2D/RectCollider/RectCollider.h"

#include <vector>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <TktkMath/MathHelper.h>
#include "TktkDX12BaseComponents/2D/CircleCollider/CircleCollider.h"
#include "TktkDX12BaseComponents/2D/Polygon2dCollider/Polygon2dCollider.h"

namespace tktk
{
	RectCollider::RectCollider(
		CollisionGroupTypeCarrier collisionGroupType,
		const tktkMath::Vector2& rectSize,
		const tktkMath::Vector2& localPosition,
		bool isExtrude,
		float extrudedRate
	)
		: ComponentBase(0.0f, collisionGroupType)
		, m_boundingPolygon2d(
			{
				tktkMath::Vector2(-rectSize.x / 2, -rectSize.y / 2) + localPosition,
				tktkMath::Vector2( rectSize.x / 2, -rectSize.y / 2) + localPosition,
				tktkMath::Vector2( rectSize.x / 2,  rectSize.y / 2) + localPosition,
				tktkMath::Vector2(-rectSize.x / 2,  rectSize.y / 2) + localPosition
			})
		, m_isExtrude(isExtrude)
		, m_extrudedRate(extrudedRate)
	{
	}

	void RectCollider::start()
	{
		m_transform2D = getComponent<Transform2D>();

		if (m_transform2D.expired())
		{
			throw std::runtime_error("RectCollider not found Transform2D");
		}
	}

	bool RectCollider::isCollide(const ComponentBasePtr& other)
	{
		// 衝突相手のコンポーネントが「RectCollider」だったら
		if (other.canCast<RectCollider>())
		{
			// 二次元ポリゴンと二次元ポリゴンで衝突判定を呼ぶ
			auto otherCollider = other.castPtr<RectCollider>();
			auto hitInfo = m_boundingPolygon2d.isCollide(otherCollider->getBoundingPolygon2d(), m_transform2D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());
			
			// 衝突相手情報と衝突結果をリストに追加する
			m_hitInfo2dPairList.push_front({ other->getGameObject(), otherCollider->isExtrud(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}

		// 衝突相手のコンポーネントが「CircleCollider」だったら
		if (other.canCast<CircleCollider>())
		{
			// 二次元ポリゴンと円で衝突判定を呼ぶ
			auto otherCollider = other.castPtr<CircleCollider>();
			auto hitInfo = m_boundingPolygon2d.isCollide(otherCollider->getBoundingCircle(), m_transform2D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// 衝突相手情報と衝突結果をリストに追加する
			m_hitInfo2dPairList.push_front({ other->getGameObject(), otherCollider->isExtrud(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}

		// 衝突相手のコンポーネントが「Polygon2dCollider」だったら
		if (other.canCast<Polygon2dCollider>())
		{
			// 二次元ポリゴンと二次元ポリゴンで衝突判定を呼ぶ
			auto otherCollider = other.castPtr<Polygon2dCollider>();
			auto hitInfo = m_boundingPolygon2d.isCollide(otherCollider->getBoundingPolygon2d(), m_transform2D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// 衝突相手情報と衝突結果をリストに追加する
			m_hitInfo2dPairList.push_front({ other->getGameObject(), otherCollider->isExtrud(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}
		return false;
	}

	void RectCollider::afterCollide()
	{
		extrusion();

		m_hitInfo2dPairList.clear();
	}

	const tktkCollision::BoundingPolygon2D& RectCollider::getBoundingPolygon2d() const
	{
		return m_boundingPolygon2d;
	}

	bool RectCollider::isExtrud() const
	{
		return m_isExtrude;
	}

	float RectCollider::getExtrudedRate() const
	{
		return m_extrudedRate;
	}

	const ComponentPtr<Transform2D>& RectCollider::getTransform() const
	{
		return m_transform2D;
	}

	void RectCollider::extrusion()
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