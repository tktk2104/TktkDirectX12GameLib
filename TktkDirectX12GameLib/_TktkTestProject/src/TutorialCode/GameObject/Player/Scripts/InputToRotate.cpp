#include "InputToRotate.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/3D/Transform3D/Transform3D.h>


void InputToRotate::update()
{
	tktkMath::Vector3 rotete = tktkMath::Vector3_v::zero;

	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_A))	rotete.y =  100.0f;
	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_D))	rotete.y = -100.0f;
	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_W))	rotete.x =  100.0f;
	if (tktk::DX12GameManager::isPush(tktk::KeybordKeyType::key_S))	rotete.x = -100.0f;

	getComponent<tktk::Transform3D>()->addLocalEulerAngles(rotete * tktk::DX12GameManager::deltaTime());
}
