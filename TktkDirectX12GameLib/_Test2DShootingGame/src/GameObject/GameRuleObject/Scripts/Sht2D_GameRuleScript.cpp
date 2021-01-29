#include "Sht2D_GameRuleScript.h"

#include "../../../Enums/Enums.h"
#include "../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"
#include "../../GamePlaySceneObjects/Ui/GameClearText/Sht2D_GameClearText.h"
#include "../../GamePlaySceneObjects/Ui/GameOverText/Sht2D_GameOverText.h"

void Sht2D_GameRuleScript::start()
{
	// プレイヤーオブジェクトを取得する
	m_playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);
}

void Sht2D_GameRuleScript::update()
{
	// プレイヤーオブジェクトが取得できなければ関数を終える
	if (m_playerObject.expired()) return;

	// プレイヤーオブジェクトから耐久力コンポーネントを取得する
	tktk::ComponentPtr<Sht2D_HealthPoint> playerHp = m_playerObject->getComponent<Sht2D_HealthPoint>();

	// プレイヤーの耐久力が０以下だったら
	if (playerHp->outOfHp())
	{
		// ゲームオーバーテキストを生成する
		Sht2D_GameOverText::create();

		// 全てのオブジェクトスポナーを削除する
		for (const auto& objectSpawner : tktk::DX12Game::findGameObjectsWithTag(GameObjectTag::ObjectSpawner))
		{
			objectSpawner->setActive(false);
		}

		// プレイヤーオブジェクトポインタを初期化する
		m_playerObject = tktk::GameObjectPtr();
	}
}

void Sht2D_GameRuleScript::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	// プレイヤーオブジェクトが取得できなければ関数を終える
	if (m_playerObject.expired()) return;

	// ゲームクリアメッセージを取得したら
	if (type.isSame(EventMessageType::GameClear))
	{
		// ゲームクリアテキストを生成する
		Sht2D_GameClearText::create();

		// プレイヤーオブジェクトポインタを初期化する
		m_playerObject = tktk::GameObjectPtr();
	}
}
