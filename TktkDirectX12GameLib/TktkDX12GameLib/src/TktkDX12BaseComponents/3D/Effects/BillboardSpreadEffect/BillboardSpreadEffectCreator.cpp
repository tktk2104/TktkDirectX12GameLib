#include "TktkDX12BaseComponents/3D/Effects/BillboardSpreadEffect/BillboardSpreadEffectCreator.h"

#include <stdexcept>
#include <TktkMath/Random.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

#include "TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h"
#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawerMaker.h"
#include "TktkDX12BaseComponents/3D/Effects/BillboardSpreadEffect/Particle/BillboardSpreadEffectParticle.h"

namespace tktk
{
	BillboardSpreadEffectCreator::BillboardSpreadEffectCreator(const BillboardSpreadEffectParam& param)
		: m_param(param)
	{
	}

	void BillboardSpreadEffectCreator::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BillboardSpreadEffectParticle not found Transform3D");
		}
	}

	void BillboardSpreadEffectCreator::onEnable()
	{
		// アクティブフラグ変更時に状態をリセットする設定の場合、
		if (m_param.changeAvtiveToReset)
		{
			// 生成状況をリセットする
			m_generateIntervalSecTimer = 0.0f;
			m_totalGenerateCounter = 0;
		}
	}

	void BillboardSpreadEffectCreator::update()
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

				// 生成座標を計算する
				auto generateLocalPosRandomRange = tktkMath::Vector3(
					tktkMath::Random::getRandF(-m_param.generateLocalPosRandomRange.x, m_param.generateLocalPosRandomRange.x),
					tktkMath::Random::getRandF(-m_param.generateLocalPosRandomRange.y, m_param.generateLocalPosRandomRange.y),
					tktkMath::Random::getRandF(-m_param.generateLocalPosRandomRange.z, m_param.generateLocalPosRandomRange.z)
				);
				auto generatePos = m_param.generateLocalPos + generateLocalPosRandomRange;

				//  子要素追加フラグが立っていなかったらワールド空間での座標になるように修正する
				if (!m_param.setChild) generatePos += m_transform->getWorldPosition();

				// ジンバルロックに注意しながら回転情報を作る
				auto rotate = tktkMath::Quaternion::createFromEulerAngle({ tktkMath::Random::getRandF(0.0f, 360.0f), 0.0f, 0.0f})
					* tktkMath::Quaternion::createFromEulerAngle({ 0.0f, tktkMath::Random::getRandF(0.0f, 360.0f),  0.0f });

				// スケールを計算する
				auto billboardScaleRandomRange = tktkMath::Vector2(
					tktkMath::Random::getRandF(-m_param.billboardScaleRandomRange.x, m_param.billboardScaleRandomRange.x),
					tktkMath::Random::getRandF(-m_param.billboardScaleRandomRange.y, m_param.billboardScaleRandomRange.y)
				);
				auto billboardScale = m_param.billboardScale + billboardScaleRandomRange;

				// 座標管理コンポーネントを作る
				Transform3DMaker::makeStart(particleObject)
					.initPosition(generatePos)
					.initRotation(rotate)
					.initScaleRate({ billboardScale.x, billboardScale.y, 1.0f })
					.create();

				// ビルボード描画コンポーネントを作る
				BillboardDrawerMaker::makeStart(particleObject)
					.billboardMaterialHandle(m_param.useBillboardHandle)
					.notClippingUseHandle(m_param.useBillboardHandle)
					.blendRate(m_param.billboardBlendRate)
					.create();

				// ビルボードパーティクル用のコンポーネントを作る
				auto moveSpeedPerSecRandomRange = tktkMath::Random::getRandF(-m_param.moveSpeedPerSecRandomRange, m_param.moveSpeedPerSecRandomRange);
				auto lifeTimeSecRandomRange		= tktkMath::Random::getRandF(-m_param.lifeTimeSecRandomRange, m_param.lifeTimeSecRandomRange);
				particleObject->createComponent<BillboardSpreadEffectParticle>(
					m_param.moveSpeedPerSec + moveSpeedPerSecRandomRange,
					m_param.lifeTimeSec + lifeTimeSecRandomRange
					);

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