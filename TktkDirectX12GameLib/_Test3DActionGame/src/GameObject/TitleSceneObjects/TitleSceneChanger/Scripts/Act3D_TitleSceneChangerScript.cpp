#include "Act3D_TitleSceneChangerScript.h"

#include "../../../../Enums/Enums.h"

void Act3D_TitleSceneChangerScript::start()
{
	m_soundPlayer = getComponent<tktk::SoundPlayer>();

	if (m_soundPlayer.expired())
	{
		throw std::runtime_error("Act3D_TitleSceneChangerScript not found SoundPlayer");
	}
}

void Act3D_TitleSceneChangerScript::update()
{
	// シーン遷移が始まっていたら
	if (m_startSceneChange)
	{
		// タイマーを更新する
		m_sceneChangeSecTimer += tktk::DX12Game::deltaTime();

		// シーン遷移が終わっていたら
		if (m_endSceneChange)
		{
			// フェード用スプライトを徐々に薄くする
			const auto& curBlendRate = m_fadeSprite->getBlendRate();
			m_fadeSprite->setBlendRate(curBlendRate - tktkMath::Color(0.0f, (1.0f / 2.0f) * tktk::DX12Game::deltaTime()));

			// 自身を殺す時間になっていたら
			if (m_sceneChangeSecTimer > SelfDeadTime)
			{
				getGameObject()->destroy();
				return;
			}

			return;
		}

		// フェード用スプライトを徐々に濃くする
		const auto& curBlendRate = m_fadeSprite->getBlendRate();
		m_fadeSprite->setBlendRate(curBlendRate + tktkMath::Color(0.0f, (1.0f / 2.0f) * tktk::DX12Game::deltaTime()));

		if (m_sceneChangeSecTimer > SceneChangeTime)
		{
			// タイトルシーンを無効化して
			tktk::DX12Game::disableScene(SceneId::Title);

			// メインシーンを有効にする
			tktk::DX12Game::enableScene(SceneId::Main);

			// シーン遷移が終わったフラグを立てる
			m_endSceneChange = true;
		}

		return;
	}

	// いずれかの入力があったら
	if (tktk::DX12Game::isTrigger(CommandId::Any))
	{
		// サウンドを再生する
		m_soundPlayer->playSound();

		// シーン遷移を開始する
		m_startSceneChange = true;

		// フェード用スプライト
		m_fadeSprite = tktk::SpriteDrawerMaker::makeStart(getGameObject())
			.drawPriority(10)
			.spriteMaterialId(SpriteId::Black4x4)
			.blendRate({ 1.0f, 0.0f })
			.create();
	}
}
