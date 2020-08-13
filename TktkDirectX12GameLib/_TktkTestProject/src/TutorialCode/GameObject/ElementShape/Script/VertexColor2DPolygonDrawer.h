#pragma once

#include <vector>
#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include <TktkDX12Game/Component/ComponentBase.h>
#include <TktkDX12BaseComponents/2D/Transform2D/Transform2D.h>
#include "../VertexColor2DPolygonVertexData.h"

class VertexColor2DPolygonDrawer
	: public tktk::ComponentBase
{
public:

	VertexColor2DPolygonDrawer(
		float drawPriority,
		const std::vector<ElementShapeVertexData>& vertexArray
	);

public:

	void start();
	void draw() const;

private:

	std::vector<ElementShapeVertexData> m_vertexArray{};

	unsigned int m_indexCount{ 0U };

	tktk::ComponentPtr<tktk::Transform2D> m_transform{  };
};