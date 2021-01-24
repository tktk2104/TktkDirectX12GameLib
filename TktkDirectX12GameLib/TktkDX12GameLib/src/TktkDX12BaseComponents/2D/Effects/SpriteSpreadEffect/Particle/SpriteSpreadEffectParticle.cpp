#include "TktkDX12BaseComponents/2D/Effects/SpriteSpreadEffect/Particle/SpriteSpreadEffectParticle.h"

#include <stdexcept>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"
#include "TktkDX12BaseComponents/2D/Transform2D/Transform2D.h"
#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawer.h"

namespace tktk
{
	SpriteSpreadEffectParticle::SpriteSpreadEffectParticle(const ComponentPtr<SpriteDrawer>& targetDrawer, float moveSpeed, const tktkMath::Vector2& scalingSize, const tktkMath::Color& blendRateChangeWidth, float lifeTimeSec)
		: m_spriteDrawer(targetDrawer)
		, m_moveSpeedPerSec(moveSpeed)
		, m_scalingSizePerSec(scalingSize)
		, m_blendRateChangeWidthPerSec(blendRateChangeWidth)
		, m_lifeSecTimer(lifeTimeSec)
	{
	}

	void SpriteSpreadEffectParticle::update()
	{
		// 生存時間が切れたら
		if (m_lifeSecTimer <= 0.0f)
		{
			// 自身とスプライトコンポーネントを殺す
			m_spriteDrawer->destroy();
			destroy();
			return;
		}

		// 上方に移動する
		auto moveVec = tktkMath::Matrix3::createRotation(m_spriteDrawer->getLocalRotationDeg()).calculateUp();
		m_spriteDrawer->addLocalPosition(moveVec * m_moveSpeedPerSec * DX12GameManager::deltaTime());

		// スケールを増加させる
		m_spriteDrawer->addLocalScaleRate(m_scalingSizePerSec * DX12GameManager::deltaTime());

		// 現在のブレンドレートを取得する
		tktkMath::Color curBlendRate = m_spriteDrawer->getBlendRate();

		// 次のフレームのブレンドレートを計算する（0.0f～1.0fの間に収める）
		curBlendRate = tktkMath::Color::clamp(curBlendRate + m_blendRateChangeWidthPerSec * DX12GameManager::deltaTime());

		// ブレンドレートを更新する
		m_spriteDrawer->setBlendRate(curBlendRate);

		// 生存時間タイマーを更新する
		m_lifeSecTimer -= DX12GameManager::deltaTime();
	}
}