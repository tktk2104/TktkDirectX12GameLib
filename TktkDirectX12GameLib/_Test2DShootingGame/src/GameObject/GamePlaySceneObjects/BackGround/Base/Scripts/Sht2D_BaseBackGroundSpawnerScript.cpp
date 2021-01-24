#include "Sht2D_BaseBackGroundSpawnerScript.h"

#include "../../../../../Enums/Enums.h"
#include "../../_Scripts/Sht2D_BackGroundScript.h"
#include "../../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"

namespace
{
	tktk::GameObjectPtr createBackGround(const tktkMath::Vector2& position, const tktkMath::Vector2& velocityPerSec, SpriteId spriteId)
	{
		auto gameObject = tktk::DX12Game::createGameObject();

		gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

		tktk::Transform2DMaker::makeStart(gameObject)
			.initPosition(position)
			.create();

		tktk::SpriteDrawerMaker::makeStart(gameObject)
			.spriteMaterialId(spriteId)
			.create();

		gameObject->createComponent<Sht2D_BackGroundScript>(velocityPerSec);

		gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
			tktkMath::Vector2(-512.0f),
			tktk::DX12Game::getScreenSize() + tktkMath::Vector2(512.0f)
			);

		return gameObject;
	}
}

void Sht2D_BaseBackGroundSpawnerScript::awake()
{
	createBackGround(FirstSpawnPos + tktkMath::Vector2(0.0f, 512.0f), VelocityPerSec, SpriteId::BackGround_Base_1);
	createBackGround(FirstSpawnPos + tktkMath::Vector2(0.0f, 1024.0f), VelocityPerSec, SpriteId::BackGround_Base_1);

	m_beforeCreatedObject = createBackGround(FirstSpawnPos, VelocityPerSec, SpriteId::BackGround_Base_1);
}

void Sht2D_BaseBackGroundSpawnerScript::update()
{
	if (m_beforeCreatedObject.expired()) return;

	auto beforeCreatedObjectTransform = m_beforeCreatedObject->getComponent<tktk::Transform2D>();

	if (beforeCreatedObjectTransform->getWorldPosition().y > 128.0f)
	{
		if (m_endSpawn)
		{
			m_beforeCreatedObject = tktk::GameObjectPtr();

			createBackGround(beforeCreatedObjectTransform->getWorldPosition() - tktkMath::Vector2(0.0f, 512.0f) + VelocityPerSec * tktk::DX12Game::deltaTime(), VelocityPerSec, SpriteId::BackGround_Base_2);

			return;
		}

		m_beforeCreatedObject = createBackGround(beforeCreatedObjectTransform->getWorldPosition() - tktkMath::Vector2(0.0f, 512.0f) + VelocityPerSec * tktk::DX12Game::deltaTime(), VelocityPerSec, SpriteId::BackGround_Base_1);
	}
}

void Sht2D_BaseBackGroundSpawnerScript::endSpawn()
{
	m_endSpawn = true;
}
