#include "CircleColliderTestScript.h"

CircleColliderTestScript::CircleColliderTestScript(float moveSpeed)
	: m_moveSpeed(moveSpeed)
{
}

void CircleColliderTestScript::start()
{
	m_transform = getComponent<tktk::Transform2D>();
}

void CircleColliderTestScript::update()
{
	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_W))
	{
		m_transform->addLocalPosition({ 0.0f, -m_moveSpeed });
	}
	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_S))
	{
		m_transform->addLocalPosition({ 0.0f, m_moveSpeed });
	}

	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_A))
	{
		m_transform->addLocalPosition({ -m_moveSpeed, 0.0f });
	}
	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_D))
	{
		m_transform->addLocalPosition({ m_moveSpeed, 0.0f });
	}
}

void CircleColliderTestScript::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	auto wireFrameDrawer = getComponent<tktk::Line2DDrawer>();

	if (wireFrameDrawer.expired()) return;

	wireFrameDrawer->setLineColor(tktkMath::Color_v::red);
}

void CircleColliderTestScript::onCollisionExit(const tktk::GameObjectPtr& other)
{
	auto wireFrameDrawer = getComponent<tktk::Line2DDrawer>();

	if (wireFrameDrawer.expired()) return;

	wireFrameDrawer->setLineColor(tktkMath::Color_v::blue);
}
