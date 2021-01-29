#include "Sht2D_BaseBackGroundSpawnerScript.h"

#include "../../../../../Enums/Enums.h"
#include "../../_Scripts/Sht2D_BackGroundScript.h"
#include "../../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"

namespace
{
	tktk::GameObjectPtr createBackGround(const tktkMath::Vector2& position, const tktkMath::Vector2& velocityPerSec, SpriteId spriteId)
	{
		// ゲームオブジェクトを作る
		tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

		// ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
		gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

		// 二次元座標管理コンポーネント
		tktk::Transform2DMaker::makeStart(gameObject)
			.initPosition(position)
			.create();

		// スプライト描画コンポーネント
		tktk::SpriteDrawerMaker::makeStart(gameObject)
			.spriteMaterialId(spriteId)
			.create();

		// 背景画像のスクロールコンポーネント（毎秒の移動速度）
		gameObject->createComponent<Sht2D_BackGroundScript>(velocityPerSec);

		// 画面外に出たら自身を殺すコンポーネント（画面範囲の左上座標、画面範囲の右下座標）
		gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
			tktkMath::Vector2(-512.0f, -512.0f),
			tktk::DX12Game::getScreenSize() + tktkMath::Vector2(512.0f, 512.0f)
			);

		return gameObject;
	}
}

void Sht2D_BaseBackGroundSpawnerScript::awake()
{
	// 初期背景を生成する
	createBackGround(FirstSpawnPos + tktkMath::Vector2(0.0f, 512.0f), VelocityPerSec, SpriteId::BackGround_Base_1);
	createBackGround(FirstSpawnPos + tktkMath::Vector2(0.0f, 1024.0f), VelocityPerSec, SpriteId::BackGround_Base_1);

	// 一番最後に生成した背景オブジェクトのポインタをメンバで保持する
	m_beforeCreatedObject = createBackGround(FirstSpawnPos, VelocityPerSec, SpriteId::BackGround_Base_1);
}

void Sht2D_BaseBackGroundSpawnerScript::update()
{
	// 前回生成した背景オブジェクトポインタが空だったらこの関数を終える
	if (m_beforeCreatedObject.expired()) return;

	// 前回生成した背景の座標管理コンポーネントを取得する
	tktk::ComponentPtr<tktk::Transform2D> beforeCreatedObjectTransform = m_beforeCreatedObject->getComponent<tktk::Transform2D>();

	// 画面の上に背景の無い領域ができそうだったら
	if (beforeCreatedObjectTransform->getWorldPosition().y > 128.0f)
	{
		// 背景の生成を止めるフラグが立っていたら
		if (m_endSpawn)
		{
			// 基地の末端背景画像オブジェクトを出現させる
			createBackGround(beforeCreatedObjectTransform->getWorldPosition() - tktkMath::Vector2(0.0f, 512.0f) + VelocityPerSec * tktk::DX12Game::deltaTime(), VelocityPerSec, SpriteId::BackGround_Base_2);

			// 前回生成した背景オブジェクトポインタを空にする
			m_beforeCreatedObject = tktk::GameObjectPtr();

			// この関数を終える
			return;
		}

		// 新たな背景画像オブジェクトを出現させる
		m_beforeCreatedObject = createBackGround(beforeCreatedObjectTransform->getWorldPosition() - tktkMath::Vector2(0.0f, 512.0f) + VelocityPerSec * tktk::DX12Game::deltaTime(), VelocityPerSec, SpriteId::BackGround_Base_1);
	}
}

void Sht2D_BaseBackGroundSpawnerScript::endSpawn()
{
	m_endSpawn = true;
}
