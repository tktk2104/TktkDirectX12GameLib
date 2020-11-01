#include "TktkDX12BaseComponents/3D/BoxCollider/BoxCollider.h"

#include <stdexcept>
#include "TktkDX12BaseComponents/3D/SphereCollider/SphereCollider.h"

namespace tktk
{
	// 立方体の頂点
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
			/* 手前の面 */
			{ tktkMath::Vector3::scale(BoxVert.at(0U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(2U), boxSize / 2.0f),  tktkMath::Vector3::scale(BoxVert.at(3U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(1U), boxSize / 2.0f)},
			/* 右の面 */
			{ tktkMath::Vector3::scale(BoxVert.at(1U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(3U), boxSize / 2.0f),  tktkMath::Vector3::scale(BoxVert.at(7U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(5U), boxSize / 2.0f)},
			/* 奥の面 */
			{ tktkMath::Vector3::scale(BoxVert.at(5U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(7U), boxSize / 2.0f),  tktkMath::Vector3::scale(BoxVert.at(6U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(4U), boxSize / 2.0f)},
			/* 左の面 */
			{ tktkMath::Vector3::scale(BoxVert.at(4U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(6U), boxSize / 2.0f),  tktkMath::Vector3::scale(BoxVert.at(2U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(0U), boxSize / 2.0f)},
			/* 上の面 */
			{ tktkMath::Vector3::scale(BoxVert.at(2U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(6U), boxSize / 2.0f),  tktkMath::Vector3::scale(BoxVert.at(7U), boxSize / 2.0f), tktkMath::Vector3::scale(BoxVert.at(3U), boxSize / 2.0f)},
			/* 下の面 */
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
		// 衝突相手のコンポーネントが「BoxCollider」だったら
		if (other.canCast<BoxCollider>())
		{
			// 三次元メッシュと三次元メッシュで衝突判定を呼ぶ
			auto otherCollider = other.castPtr<BoxCollider>();
			auto hitInfo = m_boundingMesh.isCollide(otherCollider->getBoundingMesh(), m_transform3D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// 衝突相手情報と衝突結果をリストに追加する
			m_hitInfo3dPairList.push_front({ other->getGameObject(), otherCollider->isExtrud(), otherCollider->getExtrudedRate(), hitInfo });
			return hitInfo.isHit;
		}

		// 衝突相手のコンポーネントが「SphereCollider」だったら
		if (other.canCast<SphereCollider>())
		{
			// 三次元メッシュと球体で衝突判定を呼ぶ
			auto otherCollider = other.castPtr<SphereCollider>();
			auto hitInfo = m_boundingMesh.isCollide(otherCollider->getBoundingSphere(), m_transform3D->calculateWorldMatrix(), otherCollider->getTransform()->calculateWorldMatrix());

			// 衝突相手情報と衝突結果をリストに追加する
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