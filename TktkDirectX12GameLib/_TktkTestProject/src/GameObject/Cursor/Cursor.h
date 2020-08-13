#ifndef CURSOR_H_
#define CURSOR_H_

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/2D/Transform2D/Transform2DMaker.h>
#include <TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawerMaker.h>
#include "CursorScript.h"

struct Cursor
{
	static tktk::GameObjectPtr create()
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		tktk::Transform2DMaker::makeStart(gameObject)
			.traceType(tktk::TraceParentType::notTrace)
			.create();

		tktk::SpriteDrawerMaker::makeStart(gameObject)
			.drawPriority(0.5f)
			.spriteMaterialId(0U)
			.useRtvDescriptorHeapId(0U)
			.create();

		gameObject->createComponent<CursorScript>();

		return gameObject;
	}
};
#endif // !CURSOR_H_