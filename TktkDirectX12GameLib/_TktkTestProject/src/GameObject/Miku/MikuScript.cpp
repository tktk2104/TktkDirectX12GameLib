#include "MikuScript.h"

void MikuScript::start()
{
    m_transform = getComponent<tktk::Transform3D>();
}

void MikuScript::awake()
{
}

void MikuScript::onEnable()
{
}

void MikuScript::onDisable()
{
}

void MikuScript::onDestroy()
{
}

void MikuScript::update()
{
	if (tktk::DX12GameManager::isTrigger(tktk::KeybordKeyType::key_Space))
	{
		tktk::DX12GameManager::sendMessageAll(0U, 10);
	}

	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_Space))
	{
		m_transform->addLocalEulerAngles({ 0.0f, 10.0f, 0.0f });
	}

	auto inputL = tktk::DX12GameManager::getLstick();

	if (inputL.length() > 0.3f)
	{
		m_transform->addLocalPosition(tktkMath::Vector3(inputL.x, 0.0f, inputL.y));
	}

	auto inputR = tktk::DX12GameManager::getRstick();

	if (inputR.length() > 0.3f)
	{
		m_transform->addLocalPosition(tktkMath::Vector3(inputR.x, 0.0f, inputR.y));
	}
}

void MikuScript::afterCollide()
{
}

bool MikuScript::isCollide(const tktk::ComponentBasePtr& other)
{
    return false;
}

void MikuScript::onCollisionEnter(const tktk::GameObjectPtr& other)
{
}

void MikuScript::onCollisionStay(const tktk::GameObjectPtr& other)
{
}

void MikuScript::onCollisionExit(const tktk::GameObjectPtr& other)
{
}
