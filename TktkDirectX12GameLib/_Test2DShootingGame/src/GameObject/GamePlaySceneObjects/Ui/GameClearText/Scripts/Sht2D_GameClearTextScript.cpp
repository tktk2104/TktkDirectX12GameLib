#include "Sht2D_GameClearTextScript.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_GameClearTextScript::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_GameClearTextScript not found Transform2D");
	}
}

void Sht2D_GameClearTextScript::update()
{
	if (m_textMoveEnd)
	{
		if (tktk::DX12Game::isTrigger(CommandId::Decision))
		{
			tktk::DX12Game::disableScene(SceneId::GamePlay);
			tktk::DX12Game::disableScene(SceneId::Stage1);
			tktk::DX12Game::disableScene(SceneId::Stage2);
			tktk::DX12Game::disableScene(SceneId::Stage3);

			tktk::DX12Game::enableScene(SceneId::Result);
		}
		return;
	}

	tktkMath::Vector2 curPos = m_transform->getLocalPosition();

	if (curPos.y > tktk::DX12Game::getScreenSize().y / 2.0f)
	{
		m_transform->setLocalPosition(tktkMath::Vector2(curPos.x, tktk::DX12Game::getScreenSize().y / 2.0f));

		m_textMoveEnd = true;
	}
	else
	{
		m_transform->addLocalPosition(tktkMath::Vector2(0.0f, MoveYSpeedPerSec * tktk::DX12Game::deltaTime()));
	}
}
