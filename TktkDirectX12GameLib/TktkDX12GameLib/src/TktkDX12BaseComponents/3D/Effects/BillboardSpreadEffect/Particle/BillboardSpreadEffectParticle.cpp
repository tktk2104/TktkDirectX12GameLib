#include "TktkDX12BaseComponents/3D/Effects/BillboardSpreadEffect/Particle/BillboardSpreadEffectParticle.h"

#include <stdexcept>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"
#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"

namespace tktk
{
	BillboardSpreadEffectParticle::BillboardSpreadEffectParticle(float moveSpeed, float lifeTimeSec)
		: m_moveSpeedPerSec(moveSpeed)
		, m_lifeSecTimer(lifeTimeSec)
	{
	}

	void BillboardSpreadEffectParticle::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BillboardSpreadEffectParticle not found Transform3D");
		}
	}

	void BillboardSpreadEffectParticle::update()
	{
		// 生存時間が切れたら
		if (m_lifeSecTimer <= 0.0f)
		{
			// 自身のオブジェクトを殺す
			getGameObject()->destroy();
			return;
		}

		// 前方に移動する
		m_transform->addWorldPosition(m_transform->calculateWorldForwardLH() * m_moveSpeedPerSec * DX12GameManager::deltaTime());

		// 生存時間タイマーを更新する
		m_lifeSecTimer -= DX12GameManager::deltaTime();
	}
}