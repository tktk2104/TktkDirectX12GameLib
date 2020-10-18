#include "MikuScript.h"

#include <TktkDX12BaseComponents/3D/MeshAnimator/MeshAnimator.h>

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
	if (tktk::DX12GameManager::isTrigger(tktk::KeybordKeyType::key_C))
	{
		auto camera = tktk::DX12GameManager::findGameObjectWithTag(999);

		m_transform->lookAt(camera->getComponent<tktk::Transform3D>());
	}

	//m_transform->addWorldEulerAngles({ 0.0f, 1.0f, 0.0f });

	/*if (tktk::DX12GameManager::isTrigger(tktk::KeybordKeyType::key_Space))
	{
		getComponent<tktk::MeshAnimator>()->setNewMotionId(0U, 10.0f);
	}*/

	/*if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_Space))
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
	}*/
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
