#include "Sht2D_TankEnemy.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_TankEnemyDamager.h"
#include "Scripts/Sht2D_TankEnemyTopRotator.h"
#include "Scripts/Sht2D_TankEnemyNormalBulletCreator.h"
#include "../_CommonEnemyScripts/CollisionReaction/Sht2D_EnemyCollisionReaction.h"
#include "../../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"
#include "../../../_CommonScripts/MoveForward/Sht2D_MoveForward.h"
#include "../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"

namespace
{
    // 砲台のオブジェクト
    inline tktk::GameObjectPtr createTop()
    {
        // ゲームオブジェクトを作る
        tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

        // 二次元座標管理コンポーネント
        tktk::Transform2DMaker::makeStart(gameObject)
            .create();

        // スプライト描画コンポーネント
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::TankEnemyTop)
            .create();

        // 戦車エネミーの砲塔の回転コンポーネント
        gameObject->createComponent<Sht2D_TankEnemyTopRotator>();

        // 戦車エネミーの弾発射コンポーネント
        gameObject->createComponent<Sht2D_TankEnemyNormalBulletCreator>();

        return gameObject;
    }

    // 生存ステートの準備をする
    inline void setupAliveState(tktk::GameObjectPtr gameObject)
    {
        //  生存ステートに追加する設定を行う
        gameObject->setTargetHierarchy({ TankEnemyStateTypes::Alive });
        {
            // 長方形の衝突判定コンポーネント
            tktk::RectColliderMaker::makeStart(gameObject)
                .rectSize(tktkMath::Vector2(96.0f, 128.0f))
                .collisionGroupType(CollisionGroup::Enemy)
                .create();

#ifdef _DEBUG
            // 衝突判定の境界線を描画するコンポーネント
            tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
                .lineColor(tktkMath::Color_v::red)
                .create();
#endif // _DEBUG

            // 前方に移動するコンポーネント（毎秒移動速度, 毎秒加速速度）
            gameObject->createComponent<Sht2D_MoveForward>(100.0f, 4096.0f);

            // 戦車エネミーのダメージ処理コンポーネント
            gameObject->createComponent<Sht2D_TankEnemyDamager>();

            // 戦車の砲台を自身の子供にする
            gameObject->addChild(createTop());
        }
        // 特定の状態に追加する設定を解除する
        gameObject->setTargetHierarchy({ });
    }

    // 死亡ステートの準備をする
    inline void setupDeadState(tktk::GameObjectPtr gameObject)
    {
        //  死亡ステートに追加する設定を行う
        gameObject->setTargetHierarchy({ TankEnemyStateTypes::Dead });
        {
            // 前方に移動するコンポーネント（毎秒移動速度, 毎秒加速速度）
            gameObject->createComponent<Sht2D_MoveForward>(700.0f, 1124.0f);

            // 被撃墜の煙のコンポーネント
            tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
                .spriteMaterialId(SpriteId::Spark)
                .generateLocalPosRandomRange(tktkMath::Vector2(48.0f, 48.0f))
                .generateIntervalTimeSec(0.1f)
                .generateNumPerOnce(1)
                .totalGenerateNum(-1)
                .spriteBlendRate(tktkMath::Color(1.0f, 0.5f))
                .setChild(false)
                .lifeTimeSec(1.0f)
                .moveSpeedPerSec(1024.0f)
                .spriteScale(tktkMath::Vector2(0.6f, 0.6f))
                .spriteBlendRate(tktkMath::Color(0.2f, 0.6f))
                .minGenerateAngleDeg(170.0f)
                .maxGenerateAngleDeg(190.0f)
                .blendRateChangeWidthPerSec(tktkMath::Color(0.0f, -1.0f))
                .create();

            // 爆発のスプライトアニメーションを複数生成するコンポーネント
            tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
                .generateLocalPosRandomRange(tktkMath::Vector2(128.0f, 128.0f))
                .generateIntervalTimeSec(0.2f)
                .generateNumPerOnce(1)
                .totalGenerateNum(10)
                .spriteMaterialId(SpriteId::Explosion)
                .lifeTimeSec(1.0f)
                .moveSpeedPerSec(0.0f)
                .setChild(true)
                .useAnimation(true)
                .totalAnimFrameSize(15U)
                .animSpeedRate(1.4f)
                .isLoop(false)
                .create();
        }
        // 特定の状態に追加する設定を解除する
        gameObject->setTargetHierarchy({ });
    }
}

tktk::GameObjectPtr Sht2D_TankEnemy::create(const tktkMath::Vector2& position, float rotate)
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // 敵であることを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::Enemy);

    // 敵の攻撃範囲であることを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::EnemyAttackRange);

    // ステートマシンを使用する準備を行う
    tktk::StateMachineListInitParam stateInitParam{};

    // 大元のステートは「生存」と「死亡」のどちらか
    stateInitParam.initRootNode({ TankEnemyStateTypes::Alive, TankEnemyStateTypes::Dead });

    // ステートマシンの初期化を行う
    gameObject->setupStateMachine(stateInitParam);

    // 最初は生存ステート
    gameObject->statesEnable({ TankEnemyStateTypes::Alive });

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotationDeg(rotate)
        .create();

    // 二次元慣性移動コンポーネント
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(1024.0f)
        .create();

    // スプライト描画コンポーネント
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::TankEnemyBase)
        .create();

    // キャタピラから出る煙のコンポーネント（左）
    tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Spark)
        .generateLocalPos(tktkMath::Vector2(48.0f, -48.0f))
        .generateIntervalTimeSec(0.1f)
        .generateNumPerOnce(1)
        .totalGenerateNum(-1)
        .setChild(false)
        .lifeTimeSec(4.0f)
        .moveSpeedPerSec(1024.0f)
        .spriteScale(tktkMath::Vector2(0.4f, 0.4f))
        .spriteBlendRate(tktkMath::Color(1.0f, 0.1f))
        .minGenerateAngleDeg(170.0f)
        .maxGenerateAngleDeg(190.0f)
        .blendRateChangeWidthPerSec(tktkMath::Color(0.0f, -0.1f))
        .create();

    // キャタピラから出る煙のコンポーネント（右）
    tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Spark)
        .generateLocalPos(tktkMath::Vector2(-48.0f, -48.0f))
        .generateIntervalTimeSec(0.1f)
        .generateNumPerOnce(1)
        .totalGenerateNum(-1)
        .setChild(false)
        .lifeTimeSec(4.0f)
        .moveSpeedPerSec(1024.0f)
        .spriteScale(tktkMath::Vector2(0.4f, 0.4f))
        .spriteBlendRate(tktkMath::Color(1.0f, 0.1f))
        .minGenerateAngleDeg(170.0f)
        .maxGenerateAngleDeg(190.0f)
        .blendRateChangeWidthPerSec(tktkMath::Color(0.0f, -0.1f))
        .create();

    // 接触時のダメージ（接触開始時ダメージ、毎秒の接触中ダメージ）
    gameObject->createComponent<Sht2D_DamagePower>(0.0f, 10.0f);

    // 戦車エネミー耐久力のコンポーネント（最大耐久力）
    gameObject->createComponent<Sht2D_HealthPoint>(90.0f);

    // エネミーの衝突判定リアクションコンポーネント
    gameObject->createComponent<Sht2D_EnemyCollisionReaction>();

    // 画面外に出たら自身を殺すコンポーネント（画面範囲の左上座標、画面範囲の右下座標）
    gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
        tktkMath::Vector2(-256.0f, -256.0f),
        tktk::DX12Game::getScreenSize() + tktkMath::Vector2(256.0f, 256.0f)
        );

    // 生存ステートの準備をする
    setupAliveState(gameObject);

    // 死亡ステートの準備をする
    setupDeadState(gameObject);

    return gameObject;
}