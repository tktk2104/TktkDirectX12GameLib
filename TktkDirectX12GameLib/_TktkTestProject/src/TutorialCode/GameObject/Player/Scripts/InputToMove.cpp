#include "InputToMove.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/3D/Transform3D/Transform3D.h>

void InputToMove::update()
{
	auto transform = getComponent<tktk::Transform3D>();

	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_Up))
	{
		transform->addLocalPosition(tktkMath::Vector3(0.0f, 0.0f,  10.0f) * tktk::DX12GameManager::deltaTime());
	}

	auto curPosition = transform->getLocalPosition();

	if (curPosition.z > -5.0f)
	{
		transform->setLocalPosition(tktkMath::Vector3(curPosition.x, curPosition.x,  -5.0f));
	}
	else if (curPosition.z > -10.0f)
	{
		transform->addLocalPosition(tktkMath::Vector3(0.0f, 0.0f, -5.0f) * tktk::DX12GameManager::deltaTime());
	}
	else if (curPosition.z < -10.0f)
	{
		transform->setLocalPosition(tktkMath::Vector3(curPosition.x, curPosition.x, -10.0f));
	}
}
