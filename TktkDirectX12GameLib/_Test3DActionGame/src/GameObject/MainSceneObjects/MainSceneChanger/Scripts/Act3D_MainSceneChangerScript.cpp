#include "Act3D_MainSceneChangerScript.h"

#include "../../../../Enums/Enums.h"

void Act3D_MainSceneChangerScript::start()
{
	m_fadeSprite = getComponent<tktk::SpriteDrawer>();

	if (m_fadeSprite.expired())
	{
		throw std::runtime_error("Act3D_MainSceneChanger not found SpriteDrawer");
	}
}

void Act3D_MainSceneChangerScript::update()
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

	// シーンを遷移させる時間になっていたら
	if (m_sceneChangeSecTimer > SceneChangeTime)
	{
		// メインシーンを無効化して
		tktk::DX12Game::disableScene(SceneId::Main);

		// リザルトシーンを有効にする
		tktk::DX12Game::enableScene(SceneId::Result);

		// シーン遷移が終わったフラグを立てる
		m_endSceneChange = true;
	}
}
