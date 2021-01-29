#include "Sht2D_Explosion.h"

#include "../../../../Enums/Enums.h"

#include "Script/Sht2D_ExplosionScript.h"

tktk::GameObjectPtr Sht2D_Explosion::create(
    const tktkMath::Vector2& position,
    const tktkMath::Vector2& posRandomRange,
    float intervalTimeSec,
    int totalNum,
    float effectEndTimeSec
    )
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .create();

    // 爆発のスプライトアニメーションを複数生成するコンポーネント
    tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
        .generateLocalPosRandomRange(posRandomRange)
        .generateIntervalTimeSec(intervalTimeSec)
        .generateNumPerOnce(1)
        .totalGenerateNum(totalNum)
        .spriteMaterialId(SpriteId::Explosion)
        .lifeTimeSec(1.0f)
        .moveSpeedPerSec(0.0f)
        .useAnimation(true)
        .totalAnimFrameSize(15U)
        .animSpeedRate(1.4f)
        .isLoop(false)
        .create();

    // 一定時間後に自身を殺すコンポーネント
    gameObject->createComponent<Sht2D_ExplosionScript>(effectEndTimeSec);

    return gameObject;
}
