#pragma once

#include <TktkDX12Game/Component/ComponentBase.h>

class InputToMove
	: public tktk::ComponentBase
{
public:

	InputToMove() = default;

public:

	void update();
};