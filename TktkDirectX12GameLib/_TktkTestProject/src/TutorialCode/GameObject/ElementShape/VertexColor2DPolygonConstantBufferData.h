#pragma once

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

struct VertexColor2DPolygonConstantBufferData
{
	float worldMatrix[12] 
	{ 
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f
	};
	tktkMath::Vector2 screenSize;
	float pad2[2] { 0.0f, 0.0f };
	tktkMath::Color blendRate;
};