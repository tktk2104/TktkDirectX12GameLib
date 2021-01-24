#include "TktkDX12BaseComponents/2D/Effects/SpriteSpreadEffect/SpriteSpreadEffectCreator.h"

#include <stdexcept>
#include <TktkMath/Random.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

#include "TktkDX12BaseComponents/2D/Transform2D/Transform2DMaker.h"
#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawerMaker.h"
#include "TktkDX12BaseComponents/2D/SpriteAnimator/SpriteAnimatorMaker.h"
#include "TktkDX12BaseComponents/2D/Effects/SpriteSpreadEffect/Particle/SpriteSpreadEffectParticle.h"

namespace tktk
{
	SpriteSpreadEffectCreator::SpriteSpreadEffectCreator(const SpriteSpreadEffectParam& param)
		: m_param(param)
		, m_generateIntervalSecTimer(m_param.firstGenerateTimeSec)
	{
	}

	void SpriteSpreadEffectCreator::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteSpreadEffectCreator not found Transform2D");
		}

		// パーティクルオブジェクトを作る
		m_particleObject = DX12GameManager::createGameObject();

		// 座標管理コンポーネントを作る
		Transform2DMaker::makeStart(m_particleObject)
			.create();

		// 子要素追加フラグが立っていたら子要素に追加する
		if (m_param.setChild) getGameObject()->addChild(m_particleObject);
	}

	void SpriteSpreadEffectCreator::onEnable()
	{
		// アクティブフラグ変更時に状態をリセットする設定の場合、
		if (m_param.changeAvtiveToReset)
		{
			// 生成状況をリセットする
			m_generateIntervalSecTimer = m_param.firstGenerateTimeSec;
			m_totalGenerateCounter = 0;
		}
	}

	void SpriteSpreadEffectCreator::update()
	{
		// 生成上限に達していたら生成しない
		if (m_param.totalGenerateNum > 0 && m_totalGenerateCounter == m_param.totalGenerateNum) return;

		if (m_generateIntervalSecTimer < 0.0f)
		{
			// 生成数分だけループする
			auto generateNumRandomRange = tktkMath::Random::getRandI(-m_param.generateNumPerOnceRandomRange, m_param.generateNumPerOnceRandomRange);
			for (int i = 0; i < (m_param.generateNumPerOnce + generateNumRandomRange); i++)
			{
				// 生成座標を計算する
				auto generateLocalPosRandomRange = tktkMath::Vector2(
					tktkMath::Random::getRandF(-m_param.generateLocalPosRandomRange.x, m_param.generateLocalPosRandomRange.x),
					tktkMath::Random::getRandF(-m_param.generateLocalPosRandomRange.y, m_param.generateLocalPosRandomRange.y)
				);
				auto generatePos = m_param.generateLocalPos + generateLocalPosRandomRange;

				//  子要素追加フラグが立っていなかったらワールド空間での座標になるように修正する
				if (!m_param.setChild) generatePos = generatePos * m_transform->calculateWorldMatrix();

				// ジンバルロックに注意しながら回転情報を作る
				auto rotate = tktkMath::Random::getRandF(m_param.minGenerateAngleDeg, m_param.maxGenerateAngleDeg);

				// スケールを計算する
				auto spriteScaleRandomRange = tktkMath::Vector2(
					tktkMath::Random::getRandF(-m_param.spriteScaleRandomRange.x, m_param.spriteScaleRandomRange.x),
					tktkMath::Random::getRandF(-m_param.spriteScaleRandomRange.y, m_param.spriteScaleRandomRange.y)
				);

				// スプライト描画コンポーネントを作る
				auto spriteDrawer = SpriteDrawerMaker::makeStart(m_particleObject)
					.spriteMaterialHandle(m_param.useSpriteHandle)
					.blendRate(m_param.spriteBlendRate)
					.localPosition(generatePos)
					.localRotationDeg(rotate)
					.localScaleRate(m_param.spriteScale + spriteScaleRandomRange)
					.create();

				// アニメーションを使用する設定だったら
				if (m_param.useAnimation)
				{
					SpriteAnimatorMaker::makeStart(m_particleObject)
						.targetDrawer(spriteDrawer)
						.isLoop(m_param.isLoop)
						.initFrame(m_param.initFrame)
						.animSpeedRate(m_param.animSpeedRate)
						.animFramePerSec(m_param.animFramePerSec)
						.totalAnimFrameSize(m_param.totalAnimFrameSize)
						.create();
				}

				// スプライトパーティクル用のコンポーネントを作る
				auto moveSpeedPerSecRandomRange		= tktkMath::Random::getRandF(-m_param.moveSpeedPerSecRandomRange, m_param.moveSpeedPerSecRandomRange);
				auto scalingSizePerSecRandomRange	= tktkMath::Vector2(
					tktkMath::Random::getRandF(-m_param.scalingSizePerSecRandomRange.x, m_param.scalingSizePerSecRandomRange.x),
					tktkMath::Random::getRandF(-m_param.scalingSizePerSecRandomRange.y, m_param.scalingSizePerSecRandomRange.y)
				);
				auto lifeTimeSecRandomRange			= tktkMath::Random::getRandF(-m_param.lifeTimeSecRandomRange, m_param.lifeTimeSecRandomRange);
				m_particleObject->createComponent<SpriteSpreadEffectParticle>(
					spriteDrawer,
					m_param.moveSpeedPerSec + moveSpeedPerSecRandomRange,
					m_param.scalingSizePerSec + scalingSizePerSecRandomRange,
					m_param.blendRateChangeWidthPerSec,
					m_param.lifeTimeSec + lifeTimeSecRandomRange
					);

				// 生成数カウンタをインクリメントする
				++m_totalGenerateCounter;

				// 生成上限に達したら生成を中断する
				if (m_param.totalGenerateNum > 0 && m_totalGenerateCounter == m_param.totalGenerateNum) break;
			}

			// 乱数による振れ幅も考慮して生成間隔タイマーを再設定する
			auto intervalTimeRandomRange = tktkMath::Random::getRandF(-m_param.generateIntervalTimeRandomRange, m_param.generateIntervalTimeRandomRange);
			m_generateIntervalSecTimer = m_param.generateIntervalTimeSec + intervalTimeRandomRange;
			return;
		}

		// 生成間隔タイマーを更新
		m_generateIntervalSecTimer -= DX12GameManager::deltaTime();
	}
}