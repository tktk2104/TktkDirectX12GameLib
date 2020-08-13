#pragma once

#include <TktkMath/Structs/Vector3.h>
#include <TktkDX12Game/_MainManager/DX12GameManager.h>

struct Enemy
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position);
};