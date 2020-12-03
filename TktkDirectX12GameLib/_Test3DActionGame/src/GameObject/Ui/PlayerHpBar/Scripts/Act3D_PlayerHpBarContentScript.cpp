#include "Act3D_PlayerHpBarContentScript.h"

#include "../../../../Enums/Enums.h"

void Act3D_PlayerHpBarContentScript::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_PlayerHpBarContentScript not found Transform2D");
	}
}

void Act3D_PlayerHpBarContentScript::update()
{
	// プレイヤーの能力値を取得できていなければ
	if (m_playerParam.expired())
	{
		// プレイヤーオブジェクトを取得する
		auto playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

		// プレイヤーオブジェクトを取得できなければ処理を終える
		if (playerObject.expired()) return;

		// プレイヤーの能力値のコンポーネントを取得する
		m_playerParam = playerObject->getComponent<Act3D_PlayerParam>();

		// プレイヤーの能力値のコンポーネントを取得できなければ処理を終える
		if (m_playerParam.expired()) return;
	}

	// 現在のHpの割合を参照して自身のスケールを辺かさせる
	m_transform->setLocalScaleRate({ static_cast<float>(m_playerParam->getCurHp()) / m_playerParam->getMaxHp(), m_transform->getLocalScaleRate().y});
}
