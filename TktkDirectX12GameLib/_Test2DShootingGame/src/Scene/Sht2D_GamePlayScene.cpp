#include "Sht2D_GamePlayScene.h"

#include "../GameObject/GamePlaySceneObjects/Ui/PlayerHpBar/Sht2D_PlayerHpBar.h"
#include "../GameObject/GamePlaySceneObjects/Ui/PlayerMissileCounter/Sht2D_PlayerMissileCounter.h"
#include "../GameObject/GamePlaySceneObjects/Ui/PlayerBombCounter/Sht2D_PlayerBombCounter.h"
#include "../GameObject/GamePlaySceneObjects/Player/Sht2D_Player.h"
#include "../GameObject/GameRuleObject/Sht2D_GameRuleObject.h"

void Sht2D_GamePlayScene::start()
{
	Sht2D_PlayerHpBar::create({ tktk::DX12Game::getScreenSize().x / 2.0f - 128.0f, 1000.0f });

	Sht2D_PlayerBombCounter::create({ 128.0f, 1000.0f });

	Sht2D_PlayerMissileCounter::create({ tktk::DX12Game::getScreenSize().x - 128.0f, 1000.0f });

	Sht2D_Player::create(tktk::DX12Game::getDrawGameAreaSize() * 0.5f + tktkMath::Vector2(0.0f, 256.0f));

	Sht2D_GameRuleObject::create();
}
