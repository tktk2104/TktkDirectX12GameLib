#include "Sht2D_OutGameAreaObjectDeleter.h"

Sht2D_OutGameAreaObjectDeleter::Sht2D_OutGameAreaObjectDeleter(const tktkMath::Vector2& gameAreaLeftTopPos, const tktkMath::Vector2& gameAreaRightBottomPos)
	: m_gameAreaLeftTopPos(gameAreaLeftTopPos)
	, m_gameAreaRightBottomPos(gameAreaRightBottomPos)
{
}

void Sht2D_OutGameAreaObjectDeleter::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_MoveForward not found Transform2D");
	}
}

void Sht2D_OutGameAreaObjectDeleter::update()
{
	if (m_transform->getWorldPosition().x < m_gameAreaLeftTopPos.x || m_transform->getWorldPosition().y < m_gameAreaLeftTopPos.y ||
		m_transform->getWorldPosition().x > m_gameAreaRightBottomPos.x || m_transform->getWorldPosition().y > m_gameAreaRightBottomPos.y)
	{
		getGameObject()->destroy();
	}
}
