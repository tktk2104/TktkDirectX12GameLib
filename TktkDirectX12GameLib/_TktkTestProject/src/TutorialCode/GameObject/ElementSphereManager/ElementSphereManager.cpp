#include "ElementSphereManager.h"

#include <TktkDX12Game/GameObject/GameObject.h>

#include "Script/ElementSphereManagerScript.h"

#include "../../../GameObject/GameObjectTag.h"

tktk::GameObjectPtr ElementSphereManager::create()
{
	tktk::GameObjectPtr gameObject = tktk::DX12GameManager::createGameObject();

	gameObject->addGameObjectTag(toInt(GameObjectTag::ElementSphereManager));

	gameObject->createComponent<ElementSphereManagerScript>();

	return gameObject;
}
