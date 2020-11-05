#include "TktkDX12BaseComponents/2D/Line2dDrawer/Line2DDrawer.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include <stdexcept>
#include <array>

namespace tktk
{
	Line2DDrawer::Line2DDrawer(
		float drawPriority,
		const std::vector<tktkMath::Vector2>& lineVertexArray,
		const tktkMath::Color& lineColor,
		const tktkMath::Color& blendRate,
		size_t useRtvDescriptorHeapHandle
	)
		: ComponentBase(drawPriority)
		, m_useLine2DMaterialHandle(DX12GameManager::createLine2DMaterial())
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
		, m_lineVertexArray(lineVertexArray)
		, m_lineColor(lineColor)
		, m_blendRate(blendRate)
	{

	}

	void Line2DDrawer::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
	}

	void Line2DDrawer::onDestroy()
	{
		// ラインマテリアルを削除する
		DX12GameManager::eraseLine(m_useLine2DMaterialHandle);
	}

	void Line2DDrawer::draw() const
	{
		// 描画命令に渡す頂点情報の配列が空だった場合、何もしない。
		if (m_lineVertexArray.empty()) return;

		Line2DMaterialDrawFuncArgs drawFuncArgs;
		drawFuncArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		drawFuncArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapHandle	= m_useRtvDescriptorHeapHandle;
		drawFuncArgs.worldMatrix				= m_transform->calculateWorldMatrix();
		drawFuncArgs.lineColor					= m_lineColor;
		drawFuncArgs.lineVertexArray			= m_lineVertexArray;

		DX12GameManager::drawLine(m_useLine2DMaterialHandle, drawFuncArgs);
	}

	const std::vector<tktkMath::Vector2>& Line2DDrawer::getLineVertexArray() const
	{
		return m_lineVertexArray;
	}

	void Line2DDrawer::setLineVertexArray(const std::vector<tktkMath::Vector2>& vertexArray)
	{
		m_lineVertexArray = vertexArray;
	}

	const tktkMath::Color & Line2DDrawer::getLineColor() const
	{
		return m_lineColor;
	}

	void Line2DDrawer::setLineColor(const tktkMath::Color & color)
	{
		m_lineColor = color;
	}

	void Line2DDrawer::setBlendRate(const tktkMath::Color & blendRate)
	{
		m_blendRate = blendRate;
	}
}