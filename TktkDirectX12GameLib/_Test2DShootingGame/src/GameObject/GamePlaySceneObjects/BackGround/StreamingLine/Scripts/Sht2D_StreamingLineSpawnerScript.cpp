#include "Sht2D_StreamingLineSpawnerScript.h"

#include <TktkMath/Random.h>
#include "../../../../../Enums/Enums.h"
#include "../../_Scripts/Sht2D_BackGroundScript.h"
#include "../../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"

namespace
{
	// 流れる線を生成する関数
	tktk::GameObjectPtr createStreamingLine(const tktkMath::Vector2& position, const tktkMath::Vector2& velocityPerSec)
	{
		// ゲームオブジェクトを作る
		tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

		// ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
		gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

		// 二次元座標管理コンポーネント
		tktk::Transform2DMaker::makeStart(gameObject)
			.initPosition(position)
			.initScaleRate(tktkMath::Vector2(0.1f, 0.4f))
			.create();

		// スプライト描画コンポーネント
		tktk::SpriteDrawerMaker::makeStart(gameObject)
			.spriteMaterialId(SpriteId::StreamingLine)
			.blendRate(tktkMath::Color(1.0f, 0.2f))
			.create();

		// 背景画像のスクロールコンポーネント（毎秒の移動速度）
		gameObject->createComponent<Sht2D_BackGroundScript>(velocityPerSec);

		// 画面外に出たら自身を殺すコンポーネント（画面範囲の左上座標、画面範囲の右下座標）
		gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
			tktkMath::Vector2(-128.0f, -128.0f),
			tktk::DX12Game::getScreenSize() + tktkMath::Vector2(128.0f, 128.0f)
			);

		return gameObject;
	}
}

void Sht2D_StreamingLineSpawnerScript::update()
{
	// １フレームで出現する流れる線の数だけループする
	for (size_t i = 0; i < SpawnStreamingLineCountPerFrame; i++)
	{
		// 流れる線を生成する
		createStreamingLine(tktkMath::Vector2(tktkMath::Random::getRandF(0.0f, tktk::DX12Game::getScreenSize().x), 0.0f), VelocityPerSec);
	}
}
