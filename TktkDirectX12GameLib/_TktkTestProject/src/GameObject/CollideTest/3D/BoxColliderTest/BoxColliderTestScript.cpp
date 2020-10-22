#include "BoxColliderTestScript.h"

BoxColliderTestScript::BoxColliderTestScript(float moveSpeed)
	: m_moveSpeed(moveSpeed)
{
}

void BoxColliderTestScript::start()
{
	m_transform = getComponent<tktk::Transform3D>();
}

void BoxColliderTestScript::update()
{
	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_Numpad7))
	{
		m_transform->addLocalPosition({ 0.0f, m_moveSpeed, 0.0f });
	}
	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_Numpad1))
	{
		m_transform->addLocalPosition({ 0.0f, -m_moveSpeed, 0.0f });
	}

	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_Numpad8))
	{
		m_transform->addLocalPosition({ 0.0f, 0.0f, m_moveSpeed });
	}
	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_Numpad5))
	{
		m_transform->addLocalPosition({ 0.0f, 0.0f, -m_moveSpeed });
	}

	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_Numpad4))
	{
		m_transform->addLocalPosition({ -m_moveSpeed, 0.0f, 0.0f });
	}
	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_Numpad6))
	{
		m_transform->addLocalPosition({ m_moveSpeed, 0.0f, 0.0f });
	}
}

void BoxColliderTestScript::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	auto wireFrameDrawer = getComponent<tktk::BoxMeshWireFrameDrawer>();

	if (wireFrameDrawer.expired()) return;

	wireFrameDrawer->setAlbedoColor(tktkMath::Color_v::red);
}

void BoxColliderTestScript::onCollisionExit(const tktk::GameObjectPtr& other)
{
	auto wireFrameDrawer = getComponent<tktk::BoxMeshWireFrameDrawer>();

	if (wireFrameDrawer.expired()) return;

	wireFrameDrawer->setAlbedoColor(tktkMath::Color_v::blue);
}
