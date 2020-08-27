#include "TktkDX12BaseComponents/2D/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2D.h"

#include <algorithm>
#include <TktkMath/MathHelper.h>
#include "TktkDX12BaseComponents/2D/CircleCollider/CircleCollider.h"
#include "TktkDX12BaseComponents/2D/RectCollider/RectCollider.h"
#include "TktkDX12BaseComponents/2D/Polygon2dCollider/Polygon2dCollider.h"

namespace tktk
{
	ColliderWireFrameDrawer2D::ColliderWireFrameDrawer2D(float drawPriority, const tktkMath::Color & lineColor)
		: m_drawPriority(drawPriority)
		, m_lineColor(lineColor)
	{
	}

	void ColliderWireFrameDrawer2D::start()
	{
		auto circleColliderList = getComponents<CircleCollider>();

		unsigned int curIndex = 0U;

		for (const auto & circleCollider : circleColliderList)
		{
			const tktkCollision::BoundingCircle& boundingCircle = static_cast<const tktkCollision::BoundingCircle&>(circleCollider->getBodyBase());

			std::vector<tktkMath::Vector2> vertexArray;
			vertexArray.reserve(20U + 1U);

			float baseAngle = 360.0f / 20U;

			for (unsigned int i = 0; i < 20U; i++)
			{
				vertexArray.push_back(
					tktkMath::Vector2(tktkMath::MathHelper::cos(baseAngle * i) * boundingCircle.calculateLocalRadius(), tktkMath::MathHelper::sin(baseAngle * i) * boundingCircle.calculateLocalRadius()) + boundingCircle.getLocalMatrix().calculateTranslation()
				);
			}

			vertexArray.push_back(tktkMath::Vector2(tktkMath::MathHelper::cos(0) * boundingCircle.calculateLocalRadius(), tktkMath::MathHelper::sin(0) * boundingCircle.calculateLocalRadius()) + boundingCircle.getLocalMatrix().calculateTranslation());
			
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

		auto rectColliderList = getComponents<RectCollider>();

		for (const auto & rectCollider : rectColliderList)
		{
			const tktkCollision::BoundingPolygon2d& boundingPolygon2d = static_cast<const tktkCollision::BoundingPolygon2d&>(rectCollider->getBodyBase());

			std::vector<tktkMath::Vector2> vertexArray = boundingPolygon2d.calculateLocalVertexs();
			vertexArray.push_back(boundingPolygon2d.calculateLocalVertexs().at(0));

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

		auto polygon2dColliderList = getComponents<Polygon2dCollider>();

		for (const auto & polygon2dCollider : polygon2dColliderList)
		{
			const tktkCollision::BoundingPolygon2d& boundingPolygon2d = static_cast<const tktkCollision::BoundingPolygon2d&>(polygon2dCollider->getBodyBase());

			std::vector<tktkMath::Vector2> vertexArray = boundingPolygon2d.calculateLocalVertexs();
			vertexArray.push_back(boundingPolygon2d.calculateLocalVertexs().at(0));

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
}