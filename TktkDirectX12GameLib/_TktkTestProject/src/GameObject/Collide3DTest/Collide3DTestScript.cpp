#include "Collide3DTestScript.h"

Collide3DTestScript::Collide3DTestScript(float moveSpeed)
	: m_moveSpeed(moveSpeed)
{
}

void Collide3DTestScript::start()
{
	m_transform = getComponent<tktk::Transform3D>();
}

void Collide3DTestScript::update()
{
	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_W))
	{
		m_transform->addLocalPosition({ 0.0f, 0.0f, -m_moveSpeed });
	}
	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_S))
	{
		m_transform->addLocalPosition({ 0.0f, 0.0f, m_moveSpeed });
	}

	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_A))
	{
		m_transform->addLocalPosition({ -m_moveSpeed, 0.0f, 0.0f });
	}
	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_D))
	{
		m_transform->addLocalPosition({ m_moveSpeed, 0.0f, 0.0f });
	}
}

void Collide3DTestScript::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	m_transform->addLocalScaleRate({ 1.0f, 1.0f, 1.0f });
}

void Collide3DTestScript::onCollisionStay(const tktk::GameObjectPtr& other)
{
	m_transform->addLocalEulerAngles({ 0.0f, 1.0f, 0.0f });
}

void Collide3DTestScript::onCollisionExit(const tktk::GameObjectPtr& other)
{
	getGameObject()->destroy();
}