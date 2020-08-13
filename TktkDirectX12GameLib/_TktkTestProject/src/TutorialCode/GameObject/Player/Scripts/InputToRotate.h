#pragma once

#include <TktkDX12Game/Component/ComponentBase.h>

class InputToRotate
	: public tktk::ComponentBase
{
public:

	InputToRotate() = default;

public:

	void update();
};