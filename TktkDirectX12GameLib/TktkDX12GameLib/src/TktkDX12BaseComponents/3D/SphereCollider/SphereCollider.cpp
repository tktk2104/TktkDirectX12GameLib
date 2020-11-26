#include "TktkDX12BaseComponents/3D/SphereCollider/SphereCollider.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"
#include "TktkDX12BaseComponents/3D/InertialMovement3D/InertialMovement3D.h"
#include "TktkDX12BaseComponents/3D/BoxCollider/BoxCollider.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	SphereCollider::SphereCollider(
		CollisionGroupTypeCarrier collisionGroupType,
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

		m_inertialMovement3D = getComponent<InertialMovement3D>();
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

			// 自身を押し出す距離
			auto selfExtrudeDistance = node.hitInfo.selfExtrudeVec * (selfExtrudedRate / sumExtrudedRate);

			// 押し出す距離の長さが“kEpsilon”よりも長ければ
			if (selfExtrudeDistance.length() > tktkMath::MathHelper::kEpsilon)
			{
				// 自身の押し出し処理を行う
				m_transform3D->addWorldPosition(selfExtrudeDistance);

				// 慣性移動コンポーネントを自身が持っていたら
				if (!m_inertialMovement3D.expired())
				{
					// 現在の移動速度
					auto curVelocity = m_inertialMovement3D->getVelocity();

					// 押し出す方向
					auto extrudeDirection = selfExtrudeDistance.normalized();

					// 内積を求める
					auto dotValue = tktkMath::Vector3::dot(curVelocity, extrudeDirection);

					// 押し出し方向が移動速度の反対方向だったら
					if (dotValue <= 0.0f)
					{
						// 減速する方向
						auto decreaseVelocity = extrudeDirection * dotValue;

						// 現在の速度を減速する
						m_inertialMovement3D->setVelocity(curVelocity - decreaseVelocity);
					}
				}
			}

			// 相手の座標管理コンポーネントを取得
			auto otherTransform = node.otherObject->getComponent<Transform3D>();

			// 相手を押し出す距離
			auto otherExtrudeDistance = -node.hitInfo.selfExtrudeVec * (otherExtrudedRate / sumExtrudedRate);

			// 押し出す距離の長さが“kEpsilon”よりも長ければ
			if (otherExtrudeDistance.length() > tktkMath::MathHelper::kEpsilon)
			{
				// 相手の押し出し処理を行う
				otherTransform->addWorldPosition(otherExtrudeDistance);

				// 相手の慣性移動コンポーネントを取得
				auto otherInertialMovement3D = node.otherObject->getComponent<InertialMovement3D>();

				// 慣性移動コンポーネントを相手が持っていたら
				if (!otherInertialMovement3D.expired())
				{
					// 現在の移動速度
					auto curVelocity = otherInertialMovement3D->getVelocity();

					// 押し出す方向
					auto extrudeDirection = otherExtrudeDistance.normalized();

					// 内積を求める
					auto dotValue = tktkMath::Vector3::dot(curVelocity, extrudeDirection);

					// 押し出し方向が移動速度の反対方向だったら
					if (dotValue <= 0.0f)
					{
						// 減速する方向
						auto decreaseVelocity = extrudeDirection * dotValue;

						// 現在の速度を減速する
						otherInertialMovement3D->setVelocity(curVelocity - decreaseVelocity);
					}
				}
			}
		}
	}
}