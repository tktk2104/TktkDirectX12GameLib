#pragma once

#include <vector>
#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "VertexColor2DPolygonVertexData.h"

struct ElementShape
{
	static tktk::GameObjectPtr create(const std::vector<ElementShapeVertexData>& lineVertexArray);
};