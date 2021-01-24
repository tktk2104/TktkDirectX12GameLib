#include "Sht2D_GameRuleScript.h"

#include "../../../Enums/Enums.h"
#include "../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"
#include "../../GamePlaySceneObjects/Ui/GameClearText/Sht2D_GameClearText.h"
#include "../../GamePlaySceneObjects/Ui/GameOverText/Sht2D_GameOverText.h"

void Sht2D_GameRuleScript::start()
{
	m_playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);
}

void Sht2D_GameRuleScript::update()
{
	if (m_playerObject.expired()) return;

	auto playerHp = m_playerObject->getComponent<Sht2D_HealthPoint>();

	if (playerHp->outOfHp())
	{
		Sht2D_GameOverText::create();

		auto objectSpawner = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::ObjectSpawner);

		if (!objectSpawner.expired()) objectSpawner->setActive(false);

		m_playerObject = tktk::GameObjectPtr();
	}
}

void Sht2D_GameRuleScript::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	if (type.isSame(EventMessageType::GameClear))
	{
		Sht2D_GameClearText::create();

		m_playerObject = tktk::GameObjectPtr();
	}
}
