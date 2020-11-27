#include "Act3D_PlayerAttackRangeGenerator.h"

#include "../../PlayerAttackRange/Act3D_PlayerAttackRange.h"

Act3D_PlayerAttackRangeGenerator::Act3D_PlayerAttackRangeGenerator(float generateTimeSec, float deleteTimeSec, const tktkMath::Vector3& position, const tktkMath::Vector3& scale)
	: m_generateTimeSec(generateTimeSec)
	, m_deleteTimeSec(deleteTimeSec)
{
	// プレイヤーの攻撃範囲を生成する
	m_attackRange = Act3D_PlayerAttackRange::create(position, scale);
}

void Act3D_PlayerAttackRangeGenerator::start()
{
	// プレイヤーの攻撃範囲を自身を所持するオブジェクトの子要素に設定する
	getGameObject()->addChild(m_attackRange);
}

void Act3D_PlayerAttackRangeGenerator::onEnable()
{
	// タイマーを初期化する
	m_attackRangeSecTimer = 0.0f;
}

void Act3D_PlayerAttackRangeGenerator::onDisable()
{
	// 攻撃範囲を非アクティブにする
	m_attackRange->setActive(false);
}

void Act3D_PlayerAttackRangeGenerator::update()
{
	// 攻撃範囲を削除する時間に達していなければ
	if (m_attackRangeSecTimer < m_deleteTimeSec)
	{
		// タイマーのカウントアップ
		m_attackRangeSecTimer += tktk::DX12Game::deltaTime();

		// 攻撃範囲を生成する時間に達していたらアクティブ状態にする
		if (m_attackRangeSecTimer > m_generateTimeSec) m_attackRange->setActive(true);
		return;
	}
	// 攻撃範囲を削除する時間に達していたら非アクティブ状態にする
	m_attackRange->setActive(false);
}
