#include "Sht2D_GameOverTextScript.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_GameOverTextScript::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_GameOverTextScript not found Transform2D");
	}
}

void Sht2D_GameOverTextScript::update()
{
	// テキストの移動が終わっていたら
	if (m_textMoveEnd)
	{
		// 決定入力が押され始めたら
		if (tktk::DX12Game::isTrigger(CommandId::Decision))
		{
			// ゲームプレイ関係のシーンを無効にする
			tktk::DX12Game::disableScene(SceneId::GamePlay);
			tktk::DX12Game::disableScene(SceneId::Stage1);
			tktk::DX12Game::disableScene(SceneId::Stage2);
			tktk::DX12Game::disableScene(SceneId::Stage3);

			// リザルトシーンへ遷移する
			tktk::DX12Game::enableScene(SceneId::Result);
		}
		return;
	}

	// 現在の自身の座標を取得する
	const tktkMath::Vector2& curPos = m_transform->getLocalPosition();
	
	// 現在のｙ座標が画面の中央より下にあったら
	if (curPos.y > tktk::DX12Game::getScreenSize().y / 2.0f)
	{
		// 自身の座標を画面の中心に移動する
		m_transform->setLocalPosition(tktkMath::Vector2(curPos.x, tktk::DX12Game::getScreenSize().y / 2.0f));

		// 移動終了フラグを立てる
		m_textMoveEnd = true;
	}
	// 現在のｙ座標が画面の中央より上にあったら
	else
	{
		// 自身の座標を移動する。
		m_transform->addLocalPosition(tktkMath::Vector2(0.0f, MoveYSpeedPerSec * tktk::DX12Game::deltaTime()));
	}
}
