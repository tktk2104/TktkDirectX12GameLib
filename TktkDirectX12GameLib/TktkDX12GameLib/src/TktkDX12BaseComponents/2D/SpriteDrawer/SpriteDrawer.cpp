#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

namespace tktk
{
	SpriteDrawer::SpriteDrawer(float drawPriority, unsigned int spriteMaterialId, unsigned int useRtvDescriptorHeapId)
		: ComponentBase(drawPriority)
		, m_useRtvDescriptorHeapId(useRtvDescriptorHeapId)
		, m_spriteMaterialId(spriteMaterialId)
	{
	}

	void SpriteDrawer::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
	}

	void SpriteDrawer::draw() const
	{
		SpriteMaterialDrawFuncArgs drawFuncArgs{};
		drawFuncArgs.viewportId = DX12GameManager::getSystemId(SystemViewportType::Basic);
		drawFuncArgs.scissorRectId = DX12GameManager::getSystemId(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapId = m_useRtvDescriptorHeapId;
		drawFuncArgs.worldMatrix = m_transform->calculateWorldMatrix();

		DX12GameManager::drawSprite(m_spriteMaterialId, drawFuncArgs);
	}

	void SpriteDrawer::setSpriteMaterialIdImpl(unsigned int id)
	{
		m_spriteMaterialId = id;
	}
}