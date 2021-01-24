#include "Sht2D_StreamingLineSpawnerScript.h"

#include <TktkMath/Random.h>
#include "../../../../../Enums/Enums.h"
#include "../../_Scripts/Sht2D_BackGroundScript.h"
#include "../../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"

namespace
{
	tktk::GameObjectPtr createStreamingLine(const tktkMath::Vector2& position, const tktkMath::Vector2& velocityPerSec)
	{
		auto gameObject = tktk::DX12Game::createGameObject();

		tktk::Transform2DMaker::makeStart(gameObject)
			.initPosition(position)
			.initScaleRate({ 0.1f, 0.4f })
			.create();

		tktk::SpriteDrawerMaker::makeStart(gameObject)
			.spriteMaterialId(SpriteId::StreamingLine)
			.blendRate({ 1.0, 1.0f, 1.0f, 0.2f })
			.create();

		gameObject->createComponent<Sht2D_BackGroundScript>(velocityPerSec);

		gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
			tktkMath::Vector2(-128.0f),
			tktk::DX12Game::getScreenSize() + tktkMath::Vector2(128.0f)
			);

		return gameObject;
	}
}

void Sht2D_StreamingLineSpawnerScript::update()
{
	for (size_t i = 0; i < SpawnStreamingLineCountPerFrame; i++)
	{
		createStreamingLine({ tktk::DX12Game::getScreenSize().x * tktkMath::Random::getRandF(0.0f, 1.0f), 0.0f }, VelocityPerSec);
	}
}
