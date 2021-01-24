#include "Sht2D_PlayerHpBarScript.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_PlayerHpBarScript::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_PlayerHpBarScript not found Transform2D");
	}
}

void Sht2D_PlayerHpBarScript::update()
{
	// プレイヤーの能力値を取得できていなければ
	if (m_healthPoint.expired())
	{
		// プレイヤーオブジェクトを取得する
		auto playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

		// プレイヤーオブジェクトを取得できなければ処理を終える
		if (playerObject.expired()) return;

		// プレイヤーの能力値のコンポーネントを取得する
		m_healthPoint = playerObject->getComponent<Sht2D_HealthPoint>();

		// プレイヤーの能力値のコンポーネントを取得できなければ処理を終える
		if (m_healthPoint.expired()) return;
	}

	// 現在のHpの割合を参照して自身のスケールを辺かさせる
	m_transform->setLocalScaleRate({ static_cast<float>(m_healthPoint->getCurHp()) / m_healthPoint->getMaxHp(), m_transform->getLocalScaleRate().y });
}
