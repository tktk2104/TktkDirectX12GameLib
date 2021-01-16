#include "TktkDX12BaseComponents/2D/Effects/SpriteShrinkEffect/SpriteShrinkEffectCreator.h"

#include <stdexcept>
#include <TktkMath/Random.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

#include "TktkDX12BaseComponents/2D/Transform2D/Transform2DMaker.h"
#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawerMaker.h"
#include "TktkDX12BaseComponents/2D/SpriteAnimator/SpriteAnimatorMaker.h"
#include "TktkDX12BaseComponents/2D/Effects/SpriteShrinkEffect/Particle/SpriteShrinkEffectParticle.h"

namespace tktk
{
	SpriteShrinkEffectCreator::SpriteShrinkEffectCreator(const SpriteShrinkEffectParam& param)
		: m_param(param)
		, m_generateIntervalSecTimer(m_param.firstGenerateTimeSec)
	{
	}

	void SpriteShrinkEffectCreator::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteShrinkEffectCreator not found Transform2D");
		}
	}

	void SpriteShrinkEffectCreator::onEnable()
	{
		// アクティブフラグ変更時に状態をリセットする設定の場合、
		if (m_param.changeAvtiveToReset)
		{
			// 生成状況をリセットする
			m_generateIntervalSecTimer = m_param.firstGenerateTimeSec;
			m_totalGenerateCounter = 0;
		}
	}

	void SpriteShrinkEffectCreator::update()
	{
		// 生成上限に達していたら生成しない
		if (m_param.totalGenerateNum > 0 && m_totalGenerateCounter == m_param.totalGenerateNum) return;

		if (m_generateIntervalSecTimer < 0.0f)
		{
			// 生成数分だけループする
			auto generateNumRandomRange = tktkMath::Random::getRandI(-m_param.generateNumPerOnceRandomRange, m_param.generateNumPerOnceRandomRange);
			for (int i = 0; i < (m_param.generateNumPerOnce + generateNumRandomRange); i++)
			{
				// パーティクルオブジェクトを作る
				auto particleObject = DX12GameManager::createGameObject();

				// スプライトパーティクル用のコンポーネントを作る
				auto moveSpeedPerSecRandomRange = tktkMath::Random::getRandF(-m_param.moveSpeedPerSecRandomRange, m_param.moveSpeedPerSecRandomRange);
				auto lifeTimeSecRandomRange = tktkMath::Random::getRandF(-m_param.lifeTimeSecRandomRange, m_param.lifeTimeSecRandomRange);
				particleObject->createComponent<SpriteShrinkEffectParticle>(
					m_param.moveSpeedPerSec + moveSpeedPerSecRandomRange,
					m_param.lifeTimeSec + lifeTimeSecRandomRange
					);

				// 回転情報を作る
				auto rotate = tktkMath::Random::getRandF(0.0f, 360.0f);

				// スケールを計算する
				auto billboardScaleRandomRange = tktkMath::Vector2(
					tktkMath::Random::getRandF(-m_param.spriteScaleRandomRange.x, m_param.spriteScaleRandomRange.x),
					tktkMath::Random::getRandF(-m_param.spriteScaleRandomRange.y, m_param.spriteScaleRandomRange.y)
				);

				// 収縮点座標を計算する
				auto shrinkTargetPosRandomRange = tktkMath::Vector2(
					tktkMath::Random::getRandF(-m_param.shrinkTargetPosRandomRange.x, m_param.shrinkTargetPosRandomRange.x),
					tktkMath::Random::getRandF(-m_param.shrinkTargetPosRandomRange.y, m_param.shrinkTargetPosRandomRange.y)
				);
				auto shrinkTargetPos = m_param.shrinkTargetPos + shrinkTargetPosRandomRange;

				//  子要素追加フラグが立っていなかったらワールド空間での座標になるように修正する
				if (!m_param.setChild) shrinkTargetPos = shrinkTargetPos * m_transform->calculateWorldMatrix();

				// 生成座標を計算する
				auto generatePos = shrinkTargetPos - (tktkMath::Matrix3::createRotation(rotate).calculateUp() * (m_param.moveSpeedPerSec + moveSpeedPerSecRandomRange) * (m_param.lifeTimeSec + lifeTimeSecRandomRange));

				// 座標管理コンポーネントを作る
				Transform2DMaker::makeStart(particleObject)
					.initPosition(generatePos)
					.initRotationDeg(rotate)
					.initScaleRate(m_param.spriteScale + billboardScaleRandomRange)
					.create();

				// スプライト描画コンポーネントを作る
				SpriteDrawerMaker::makeStart(particleObject)
					.spriteMaterialHandle(m_param.useSpriteHandle)
					.blendRate(m_param.spriteBlendRate)
					.create();

				// アニメーションを使用する設定だったら
				if (m_param.useAnimation)
				{
					SpriteAnimatorMaker::makeStart(particleObject)
						.isLoop(m_param.isLoop)
						.initFrame(m_param.initFrame)
						.animSpeedRate(m_param.animSpeedRate)
						.animFramePerSec(m_param.animFramePerSec)
						.totalAnimFrameSize(m_param.totalAnimFrameSize)
						.create();
				}

				// 子要素追加フラグが立っていたら子要素に追加する
				if (m_param.setChild) getGameObject()->addChild(particleObject);

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