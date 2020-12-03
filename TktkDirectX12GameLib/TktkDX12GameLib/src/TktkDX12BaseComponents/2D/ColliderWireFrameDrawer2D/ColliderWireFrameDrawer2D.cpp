#include "TktkDX12BaseComponents/2D/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2D.h"

#include <algorithm>
#include <TktkMath/MathHelper.h>
#include "TktkDX12BaseComponents/2D/Line2dDrawer/Line2DDrawer.h"
#include "TktkDX12BaseComponents/2D/CircleCollider/CircleCollider.h"
#include "TktkDX12BaseComponents/2D/RectCollider/RectCollider.h"
#include "TktkDX12BaseComponents/2D/Polygon2dCollider/Polygon2dCollider.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

// 円を正多角形で表す時の頂点数
constexpr size_t CircleVertexNum{ 20U };

// 円を正多角形で表す時の角の角度
constexpr float CircleCornerAngle{ 360.0f / CircleVertexNum };

namespace tktk
{
	ColliderWireFrameDrawer2D::ColliderWireFrameDrawer2D(float drawPriority, const tktkMath::Color & lineColor)
		: m_drawPriority(drawPriority)
		, m_lineColor(lineColor)
	{
	}

	void ColliderWireFrameDrawer2D::start()
	{
		// 各衝突判定コンポーネント毎に二次元線描画コンポーネントを作る
		createCircleColliderWireFrameDrawer();
		createRectColliderWireFrameDrawer();
		createPolygon2dColliderWireFrameDrawer();
	}

	void ColliderWireFrameDrawer2D::onEnable()
	{
		std::for_each(
			std::begin(m_wireFrameDrawerArray),
			std::end(m_wireFrameDrawerArray),
			[](const ComponentPtr<Line2DDrawer>& wireFrameDrawer) { wireFrameDrawer->setActive(true); }
		);
	}

	void ColliderWireFrameDrawer2D::onDisable()
	{
		std::for_each(
			std::begin(m_wireFrameDrawerArray),
			std::end(m_wireFrameDrawerArray),
			[](const ComponentPtr<Line2DDrawer>& wireFrameDrawer) { wireFrameDrawer->setActive(false); }
		);
	}

	void ColliderWireFrameDrawer2D::createCircleColliderWireFrameDrawer()
	{
		auto circleColliderList = getComponents<CircleCollider>();

		for (const auto& circleCollider : circleColliderList)
		{
			const tktkCollision::BoundingCircle& boundingCircle = circleCollider->getBoundingCircle();

			// 円を正多角形で表す為の頂点
			std::vector<tktkMath::Vector2> vertexArray;
			vertexArray.reserve(20U + 1U);

			// 各頂点を計算する
			for (size_t i = 0; i < CircleVertexNum; i++)
			{
				vertexArray.push_back(
					tktkMath::Vector2(tktkMath::MathHelper::cos(CircleCornerAngle * i) * boundingCircle.getRadius(), tktkMath::MathHelper::sin(CircleCornerAngle * i) * boundingCircle.getRadius())
					+ boundingCircle.getCenterPosition()
				);
			}

			// 多角形を閉じる
			vertexArray.push_back(tktkMath::Vector2(boundingCircle.getRadius(), 0.0f) + boundingCircle.getCenterPosition());

			// 二次元線描画コンポーネントを作る
			m_wireFrameDrawerArray.push_back(
				getGameObject()->createComponent<Line2DDrawer>(
					m_drawPriority,
					vertexArray,
					m_lineColor,
					tktkMath::Color_v::white,
					DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer)
					)
			);
		}
	}

	void ColliderWireFrameDrawer2D::createRectColliderWireFrameDrawer()
	{
		auto rectColliderList = getComponents<RectCollider>();

		for (const auto& rectCollider : rectColliderList)
		{
			const tktkCollision::BoundingPolygon2D& boundingPolygon2d = rectCollider->getBoundingPolygon2d();

			// 二次元ポリゴンの頂点を取得し、ライン描画に必要な“多角形を閉じる頂点”を追加する
			std::vector<tktkMath::Vector2> vertexArray = boundingPolygon2d.getVertexs();
			vertexArray.push_back(boundingPolygon2d.getVertexs().at(0U));

			// 二次元線描画コンポーネントを作る
			m_wireFrameDrawerArray.push_back(
				getGameObject()->createComponent<Line2DDrawer>(
					m_drawPriority,
					vertexArray,
					m_lineColor,
					tktkMath::Color_v::white,
					DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer)
					)
			);
		}
	}

	void ColliderWireFrameDrawer2D::createPolygon2dColliderWireFrameDrawer()
	{
		auto polygon2dColliderList = getComponents<Polygon2dCollider>();

		for (const auto& polygon2dCollider : polygon2dColliderList)
		{
			const tktkCollision::BoundingPolygon2D& boundingPolygon2d = polygon2dCollider->getBoundingPolygon2d();

			// 二次元ポリゴンの頂点を取得し、ライン描画に必要な“多角形を閉じる頂点”を追加する
			std::vector<tktkMath::Vector2> vertexArray = boundingPolygon2d.getVertexs();
			vertexArray.push_back(boundingPolygon2d.getVertexs().at(0U));

			// 二次元線描画コンポーネントを作る
			m_wireFrameDrawerArray.push_back(
				getGameObject()->createComponent<Line2DDrawer>(
					m_drawPriority,
					vertexArray,
					m_lineColor,
					tktkMath::Color_v::white,
					DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer)
					)
			);
		}
	}
}