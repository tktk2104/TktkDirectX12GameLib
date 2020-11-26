#include "Act3D_PlayerController.h"

#include <TktkMath/MathHelper.h>
#include "../../../../../Enums/Enums.h"

Act3D_PlayerController::Act3D_PlayerController(float moveSpeedPerSec, float rotateDegSpeedPerSec)
	: m_moveSpeedPerSec(moveSpeedPerSec)
	, m_rotateDegSpeedPerSec(rotateDegSpeedPerSec)
{
}

void Act3D_PlayerController::start()
{
	m_transform = getComponent<tktk::Transform3D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_PlayerController not found Transform3D");
	}
}

void Act3D_PlayerController::update()
{
	// 移動処理を行う
	move();

	// 回転処理を行う
	rotate();
}

void Act3D_PlayerController::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	if (!isActive()) return;

	// 敵の方を向かせるメッセージが届いたら
	if (type.isSame(EventMessageType::LookToEnemy))
	{
		// 最も近い敵の方を向く処理を行う
		lookMostNearEnemy();
	}
}

void Act3D_PlayerController::move()
{
	// 移動に関係するステートを一旦全て切る
	getGameObject()->stateDisable(PlayerStateType::Idle);
	getGameObject()->stateDisable(PlayerStateType::WalkForward);
	getGameObject()->stateDisable(PlayerStateType::WalkBackward);
	getGameObject()->stateDisable(PlayerStateType::WalkLeft);
	getGameObject()->stateDisable(PlayerStateType::WalkRight);
	getGameObject()->stateDisable(PlayerStateType::RunForward);

	// 次の移動に関するステート
	auto playerMoveState = PlayerStateType::Idle;

	// 移動速度
	auto moveSpeed = m_moveSpeedPerSec;

	// プレイヤーの移動入力を取得する
	auto inputMoveVec = tktk::DX12Game::moveVec();

	// 最も強い移動入力の値
	auto mostStrongMoveInputPower = 0.0f;

	// 入力方向によってプレイヤーの移動ステートを変える
	if (inputMoveVec.y > mostStrongMoveInputPower)
	{
		playerMoveState = PlayerStateType::WalkForward;
		mostStrongMoveInputPower = inputMoveVec.y;
	}
	if (inputMoveVec.y < -mostStrongMoveInputPower)
	{
		playerMoveState = PlayerStateType::WalkBackward;
		mostStrongMoveInputPower = -inputMoveVec.y;
	}
	if (inputMoveVec.x < -mostStrongMoveInputPower)
	{
		playerMoveState = PlayerStateType::WalkLeft;
		mostStrongMoveInputPower = -inputMoveVec.x;
	}
	if (inputMoveVec.x > mostStrongMoveInputPower)
	{
		playerMoveState = PlayerStateType::WalkRight;
		mostStrongMoveInputPower = inputMoveVec.x;
	}

	// もし前方移動状態の場合、
	if (playerMoveState == PlayerStateType::WalkForward)
	{
		// 走りボタンが入力されていたら
		if (tktk::DX12Game::isPush(CommandId::Run))
		{
			// プレイヤーを前方走り状態にする
			playerMoveState = PlayerStateType::RunForward;

			// 移動速度を早くする
			moveSpeed *= 2.0f;
		}
	}

	// 入力から移動方向を計算する
	auto moveDir = tktkMath::Vector3(inputMoveVec.x, 0.0f, inputMoveVec.y) * m_transform->getWorldRotation();

	// 自身の座標管理コンポーネントに座標移動量を渡す
	m_transform->addWorldPosition(moveDir * moveSpeed * tktk::DX12Game::deltaTime());

	// 新たな移動ステートを設定する
	getGameObject()->stateEnable(playerMoveState);
}

void Act3D_PlayerController::rotate()
{
	// 敵を見るボタンが押されていたら
	if (tktk::DX12Game::isPush(CommandId::LookEnemy))
	{
		// 最も近い敵の方を向く処理を行う
		lookMostNearEnemy();
	}

	// プレイヤーの視点移動入力を取得する
	auto inputMoveVec = tktk::DX12Game::lookVec();

	// 自身の座標管理コンポーネントに回転変化量を渡す
	m_transform->addLocalEulerAngles({ 0.0f,  inputMoveVec.x * m_rotateDegSpeedPerSec * tktk::DX12Game::deltaTime(), 0.0f });
}

void Act3D_PlayerController::lookMostNearEnemy()
{
	// エネミーオブジェクトのリストを取得する
	auto enemyObjects = tktk::DX12Game::findGameObjectsWithTag(GameObjectTag::Enemy);

	// 敵が存在しなければ処理を終える
	if (enemyObjects.empty()) return;

	// 最も近い敵への距離
	auto minDist = std::numeric_limits<float>::max();

	// 最も近い敵の座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D> nearEnemyTransform;

	// 全てのエネミーオブジェクトを巡回する
	for (const auto& enemyObject : enemyObjects)
	{
		// 座標管理コンポーネントの一時保存変数
		auto tempEnemyTransform = enemyObject->getComponent<tktk::Transform3D>();

		// プレイヤーとエネミーの距離を求める
		auto dist = tktkMath::Vector3::distance(m_transform->getWorldPosition(), tempEnemyTransform->getWorldPosition());

		// 距離の近さを更新していたら
		if (dist < minDist)
		{
			// もっとも近い敵の座標管理コンポーネントを更新する
			nearEnemyTransform = tempEnemyTransform;

			// 最も近い距離を更新する
			minDist = dist;
		}
	}

	// 自身が向くべき方向のベクトルを求める
	auto rotateDir = nearEnemyTransform->getWorldPosition() - m_transform->getWorldPosition();

	// 自身の座標管理コンポーネントに向くべき回転方向を渡す
	m_transform->setLocalEulerAngles({ 0.0f, tktkMath::Vector2::signedAngle({ rotateDir.x, rotateDir.z }, tktkMath::Vector2_v::up), 0.0f });
}
