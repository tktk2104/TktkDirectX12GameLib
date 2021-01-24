#include "Sht2D_PlayerMissileCreator.h"

#include <limits>
#include "../../../../Enums/Enums.h"
#include "../../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"
#include "../../PlayerBullets/PlayerMissile/Sht2D_PlayerMissile.h"
#include "../../Ui/LockOnIcon/Sht2D_LockOnIcon.h"

void Sht2D_PlayerMissileCreator::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_PlayerMissileCreator not found Transform2D");
	}

	m_playerBulletCount = getComponent<Sht2D_PlayerBulletCount>();

	if (m_playerBulletCount.expired())
	{
		throw std::runtime_error("Sht2D_PlayerMissileCreator not found Sht2D_PlayerBulletCount");
	}
}

void Sht2D_PlayerMissileCreator::update()
{
	// 発射間隔タイマーがまだ０より大きければ
	if (m_shotIntervalSecTimer > 0.0f)
	{
		// カウントダウンして処理を終える
		m_shotIntervalSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	// ミサイルの残弾数が０だったら処理を終える
	if (m_playerBulletCount->getCurMissileCount() <= 0) return;

	// ミサイル発射ボタンが押され始めたら
	if (tktk::DX12Game::isTrigger(CommandId::ShotMissile))
	{
		// ロックオン対象を取得する
		auto lockOnEnemyArray = findForwardLockOnEnemy(2U);

		// ロックオン対象が１体でも存在したら
		if (lockOnEnemyArray.size() >= 1U)
		{
			// ロックオンアイコンを２つ生成する
			m_lockOnIconObjectArray = { Sht2D_LockOnIcon::create(), Sht2D_LockOnIcon::create() };

			// 一体目の敵をロックオンする
			lockOnEnemyArray.at(0U)->addChild(m_lockOnIconObjectArray.at(0U));

			// ロックオン対象が２体存在したら
			if (lockOnEnemyArray.size() >= 2U)
			{
				// 二体目の敵をロックオンする
				lockOnEnemyArray.at(1U)->addChild(m_lockOnIconObjectArray.at(1U));
			}
			// ロックオン対象が１体だったら
			else
			{
				// 一体目の敵を二重ロックオンする
				lockOnEnemyArray.at(0U)->addChild(m_lockOnIconObjectArray.at(1U));
			}
		}

		// 入力時間タイマーをカウントアップ
		m_pushingSecTimer += tktk::DX12Game::deltaTime();

		return;
	}

	// ミサイル発射ボタンが押されていたら
	if (tktk::DX12Game::isPush(CommandId::ShotMissile))
	{
		// 入力時間タイマーをカウントアップ
		m_pushingSecTimer += tktk::DX12Game::deltaTime();

		// ロックオンが終わっていなければ
		if (m_pushingSecTimer < MissileLockOnTimeSec)
		{
			// ロックオンアイコンを収縮させる
			for (tktk::GameObjectPtr& lockOnIconObject : m_lockOnIconObjectArray)
			{
				if (lockOnIconObject.expired()) continue;

				lockOnIconObject->getComponent<tktk::Transform2D>()->setLocalScaleRate({ 1.0f - (m_pushingSecTimer / MissileLockOnTimeSec) });
			}
		}
		else if (!m_lockOnReady)
		{
			for (tktk::GameObjectPtr& lockOnIconObject : m_lockOnIconObjectArray)
			{
				if (lockOnIconObject.expired()) continue;

				lockOnIconObject->getComponent<tktk::Transform2D>()->setLocalScaleRate(tktkMath::Vector2_v::one);
				lockOnIconObject->getComponent<tktk::SpriteDrawer>()->setSpriteMaterialId(SpriteId::LockOnReady);
			}

			m_lockOnReady = true;
		}
	}

	// ミサイル発射ボタンが離されて、入力時間タイマーがカウントアップしていたら
	else if(m_pushingSecTimer > 0.0f)
	{
		// ミサイルを発射する
		shotMissile();

		// 入力時間タイマーをリセットする
		m_pushingSecTimer = 0.0f;

		for (tktk::GameObjectPtr& lockOnIconObject : m_lockOnIconObjectArray)
		{
			if (!lockOnIconObject.expired()) lockOnIconObject->destroy();
		}
	}
}

std::vector<tktk::GameObjectPtr> Sht2D_PlayerMissileCreator::findForwardLockOnEnemy(size_t maxFindNum) const
{
	struct FindEnemyParam
	{
		tktk::GameObjectPtr object;
		float				dist;
		tktkMath::Vector2	pos;
	};

	// 参照した敵の数
	size_t refEnemyCount = 0U;

	// 敵の情報をプレイヤーに近い順に代入するリスト
	std::forward_list<FindEnemyParam> findEnemyParamList;

	// 全ての敵オブジェクトをループする
	for (const auto& enemy : tktk::DX12Game::findGameObjectsWithTag(GameObjectTag::Enemy))
	{
		// 期限切れポインタだったら次の要素へ
		if (enemy.expired()) continue;

		// 死んでいる敵だったら次の要素へ
		if (enemy->getComponent<Sht2D_HealthPoint>()->outOfHp()) continue;

		// 敵の座標管理コンポーネントを取得する
		auto enemyTransform = enemy->getComponent<tktk::Transform2D>();

		// ロックオン範囲外の敵だったら何もしない
		if (tktkMath::Vector2::angle(m_transform->calculateWorldUp(), enemyTransform->getWorldPosition() - m_transform->getWorldPosition()) > MissileLockOnAngleRangeDeg) continue;

		// 敵との距離を計算する
		float selfEnemyPosDist = tktkMath::Vector2::distance(m_transform->getWorldPosition(), enemyTransform->getWorldPosition());

		// 検索結果最大数に達していなければ問答無用で追加する
		if (refEnemyCount++ < maxFindNum)
		{
			findEnemyParamList.push_front({ enemy, selfEnemyPosDist, enemyTransform->getWorldPosition() });
		}
		else
		{
			// 敵との距離の短さを更新しているかを判定する
			for (auto& findEnemyParam : findEnemyParamList)
			{
				// 短さを更新していたらその値を更新する
				if (selfEnemyPosDist < findEnemyParam.dist)
				{
					findEnemyParam = { enemy, selfEnemyPosDist, enemyTransform->getWorldPosition() };
					break;
				}
			}
		}

		// 検索結果最大数に達した瞬間に、近い順になるように要素をソートする
		if (refEnemyCount == maxFindNum) findEnemyParamList.sort([](const FindEnemyParam& first, const FindEnemyParam& second) { return first.dist > second.dist; });
	}

	// ｘ座標が小さい順になるように要素をソートする
	findEnemyParamList.sort([](const FindEnemyParam& first, const FindEnemyParam& second) { return first.pos.x < second.pos.x; });

	// 検索結果を代入する配列
	std::vector<tktk::GameObjectPtr> result;

	// 検索結果分だけ配列の要素を確保する
	result.reserve((refEnemyCount < maxFindNum) ? refEnemyCount : maxFindNum);

	// 検索結果を代入する
	for (const auto& findEnemyParam : findEnemyParamList)
	{
		result.push_back(findEnemyParam.object);
	}

	return result;
}

void Sht2D_PlayerMissileCreator::shotMissile()
{
	// ロックオン対象の配列
	std::array<tktk::GameObjectPtr, 2U> lockOntargetObjectArray;

	// ロックオンが完了していたら
	if (m_lockOnReady)
	{
		// ロックオンアイコンからロックオン対象を取得する
		for (size_t i = 0; i < 2U; i++)
		{
			if (m_lockOnIconObjectArray.at(i).expired()) continue;

			lockOntargetObjectArray.at(i) = m_lockOnIconObjectArray.at(i)->getParent();
		}
	}

	// ミサイルを１発発射する
	Sht2D_PlayerMissile::create(tktkMath::Vector2(-32.0f, 0.0f) * m_transform->calculateWorldMatrix(), -InitVelocity, m_transform->getWorldRotationDeg(), MissileSpeedPerSec, MissileAccelerationPerSec, MissileActiveTimeSec, lockOntargetObjectArray.at(0U));

	// ミサイル残弾数を１減らす
	m_playerBulletCount->changeMissileCount(-1);

	// ミサイル残弾数がまだ残っていたら
	if (m_playerBulletCount->getCurMissileCount() > 0)
	{
		// ミサイルをもう１発発射する
		Sht2D_PlayerMissile::create(tktkMath::Vector2(32.0f, 0.0f) * m_transform->calculateWorldMatrix(), InitVelocity, m_transform->getWorldRotationDeg(), MissileSpeedPerSec, MissileAccelerationPerSec, MissileActiveTimeSec, lockOntargetObjectArray.at(1U));

		// ミサイル残弾数を１減らす
		m_playerBulletCount->changeMissileCount(-1);
	}

	// ロックオン完了フラグを切る
	m_lockOnReady = false;

	// 発射間隔タイマーをセットする
	m_shotIntervalSecTimer = ShotIntervalTimeSec;
}
