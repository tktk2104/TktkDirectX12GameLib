#include "CollideTestScript.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

CollideTestScript::CollideTestScript(float moveSpeed)
	: m_moveSpeed(moveSpeed)
{
}

void CollideTestScript::start()
{
	m_transform = getComponent<tktk::Transform2D>();
}

void CollideTestScript::update()
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

void CollideTestScript::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	m_transform->addLocalScaleRate({ 1.0f, 1.0f });
}

void CollideTestScript::onCollisionStay(const tktk::GameObjectPtr& other)
{
	m_transform->addLocalRotationDeg(1.0f);
}

void CollideTestScript::onCollisionExit(const tktk::GameObjectPtr& other)
{
	getGameObject()->destroy();
}
