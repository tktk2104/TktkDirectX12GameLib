#include "ElementShape.h"

#include <TktkDX12BaseComponents/2D/Transform2D/Transform2DMaker.h>

#include "Script/VertexColor2DPolygonDrawer.h"
#include "Script/ElementShapeScript.h"

tktk::GameObjectPtr ElementShape::create(const std::vector<ElementShapeVertexData>& lineVertexArray)
{
	tktk::GameObjectPtr gameObject = tktk::DX12GameManager::createGameObject();

	tktk::Transform2DMaker::makeStart(gameObject)
		.create();

	gameObject->createComponent<VertexColor2DPolygonDrawer>(
		100.0f,
		lineVertexArray
		);

	gameObject->createComponent<ElementShapeScript>(lineVertexArray);

	return gameObject;
}
