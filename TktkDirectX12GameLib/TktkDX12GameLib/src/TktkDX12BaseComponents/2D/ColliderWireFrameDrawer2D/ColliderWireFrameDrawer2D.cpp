#include "TktkDX12BaseComponents/2D/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2D.h"

#include <algorithm>
#include <TktkMath/MathHelper.h>
#include "TktkDX12BaseComponents/2D/Line2dDrawer/Line2DDrawer.h"
#include "TktkDX12BaseComponents/2D/CircleCollider/CircleCollider.h"
#include "TktkDX12BaseComponents/2D/RectCollider/RectCollider.h"
#include "TktkDX12BaseComponents/2D/Polygon2dCollider/Polygon2dCollider.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

// �~�𐳑��p�`�ŕ\�����̒��_��
constexpr size_t CircleVertexNum{ 20U };

// �~�𐳑��p�`�ŕ\�����̊p�̊p�x
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
		// �e�Փ˔���R���|�[�l���g���ɓ񎟌����`��R���|�[�l���g�����
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

			// �~�𐳑��p�`�ŕ\���ׂ̒��_
			std::vector<tktkMath::Vector2> vertexArray;
			vertexArray.reserve(20U + 1U);

			// �e���_���v�Z����
			for (size_t i = 0; i < CircleVertexNum; i++)
			{
				vertexArray.push_back(
					tktkMath::Vector2(tktkMath::MathHelper::cos(CircleCornerAngle * i) * boundingCircle.getRadius(), tktkMath::MathHelper::sin(CircleCornerAngle * i) * boundingCircle.getRadius())
					+ boundingCircle.getCenterPosition()
				);
			}

			// ���p�`�����
			vertexArray.push_back(tktkMath::Vector2(boundingCircle.getRadius(), 0.0f) + boundingCircle.getCenterPosition());

			// �񎟌����`��R���|�[�l���g�����
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

			// �񎟌��|���S���̒��_���擾���A���C���`��ɕK�v�ȁg���p�`����钸�_�h��ǉ�����
			std::vector<tktkMath::Vector2> vertexArray = boundingPolygon2d.getVertexs();
			vertexArray.push_back(boundingPolygon2d.getVertexs().at(0U));

			// �񎟌����`��R���|�[�l���g�����
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

			// �񎟌��|���S���̒��_���擾���A���C���`��ɕK�v�ȁg���p�`����钸�_�h��ǉ�����
			std::vector<tktkMath::Vector2> vertexArray = boundingPolygon2d.getVertexs();
			vertexArray.push_back(boundingPolygon2d.getVertexs().at(0U));

			// �񎟌����`��R���|�[�l���g�����
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