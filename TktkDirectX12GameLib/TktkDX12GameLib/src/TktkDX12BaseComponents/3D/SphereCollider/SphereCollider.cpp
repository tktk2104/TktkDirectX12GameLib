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
		// 衝突相手のコンポーネントが「BoxCollider」だったら
		if (other.canCast<BoxCollider>())
		{
			// 球体と三次元メッシュで衝突判定を呼ぶ
			auto otherCollider = other.castPtr<BoxCollider>();
			auto hitInfo = m_boundingSphere.isCollide(otherCollider->getBoundingMesh(), m_transform3D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// 衝突相手情報と衝突結果をリストに追加する
			m_hitInfo3dPairList.push_front({ other->getGameObject(), otherCollider->isExtrud(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}

		// 衝突相手のコンポーネントが「SphereCollider」だったら
		if (other.canCast<SphereCollider>())
		{
			// 球体と球体で衝突判定を呼ぶ
			auto otherCollider = other.castPtr<SphereCollider>();
			auto hitInfo = m_boundingSphere.isCollide(otherCollider->getBoundingSphere(), m_transform3D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// 衝突相手情報と衝突結果をリストに追加する
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
			// 相手が自身を押し出そうとしていたら、自身の押し出されやすさを適応する
			float selfExtrudedRate = (node.isExtrude) ? m_extrudedRate : 0.0f;

			// 相手を押し出す設定の場合、相手の押し出されやすさを適応する
			float otherExtrudedRate = (m_isExtrude) ? node.otherExtrudedRate : 0.0f;

			// 押し出されやすさの合計を求める
			float sumExtrudedRate = selfExtrudedRate + otherExtrudedRate;

			// ゼロで割ろうとしたら緊急回避
			if (sumExtrudedRate == 0.0f) continue;

			// 自身の押し出し処理を行う
			m_transform3D->addWorldPosition(node.hitInfo.selfExtrudeVec * (selfExtrudedRate / sumExtrudedRate));

			// 相手の座標管理コンポーネントを取得
			auto otherTransform = node.otherObject->getComponent<tktk::Transform3D>();

			// 相手の押し出し処理を行う
			otherTransform->addWorldPosition(-node.hitInfo.selfExtrudeVec * (otherExtrudedRate / sumExtrudedRate));
		}
	}
}