#include "Sht2D_Player.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Sht2D_PlayerBulletCount.h"
#include "Scripts/Sht2D_PlayerMoveScript.h"
#include "Scripts/Sht2D_PlayerNormalBulletCreator.h"
#include "Scripts/Sht2D_PlayerMissileCreator.h"
#include "Scripts/Sht2D_PlayerBombCreator.h"
#include "Scripts/Sht2D_PlayerCollisionReaction.h"
#include "Scripts/Sht2D_PlayerDamager.h"
#include "../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"
#include "../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"
#include "../../_CommonScripts/MoveForward/Sht2D_MoveForward.h"
#include "../Effects/Flame/Sht2D_Flame.h"

namespace
{
    // 生存ステートの準備をする
    inline void setupAliveState(tktk::GameObjectPtr gameObject)
    {
        //  生存ステートに追加する設定を行う
        gameObject->setTargetHierarchy({ PlayerStateType::Alive });
        {
            // 長方形の衝突判定コンポーネント
            tktk::RectColliderMaker::makeStart(gameObject)
                .rectSize({ 32.0f, 88.0f })
                .collisionGroupType(CollisionGroup::Player)
                .create();

#ifdef _DEBUG
            // 衝突判定の境界線を描画するコンポーネント
            tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
                .lineColor(tktkMath::Color_v::blue)
                .create();
#endif // _DEBUG

            // プレイヤー移動コンポーネント
            gameObject->createComponent<Sht2D_PlayerMoveScript>();

            // プレイヤー通常弾発射コンポーネント
            gameObject->createComponent<Sht2D_PlayerNormalBulletCreator>();

            // プレイヤーミサイル発射コンポーネント
            gameObject->createComponent<Sht2D_PlayerMissileCreator>();

            // プレイヤーボム発射コンポーネント
            gameObject->createComponent<Sht2D_PlayerBombCreator>();

            // プレイヤーのダメージ処理コンポーネント
            gameObject->createComponent<Sht2D_PlayerDamager>();

            // 炎エフェクトオブジェクトを自身の子要素に
            gameObject->addChild(Sht2D_Flame::create({ 0.0f, 34.0f }, 180.0f));
        }
        // 特定の状態に追加する設定を解除する
        gameObject->setTargetHierarchy({ });
    }

    // 死亡ステートの準備をする
    inline void setupDeadState(tktk::GameObjectPtr gameObject)
    {
        //  死亡ステートに追加する設定を行う
        gameObject->setTargetHierarchy({ PlayerStateType::Dead });
        {
            // 前方に移動するコンポーネント（毎秒移動速度, 毎秒加速速度）
            gameObject->createComponent<Sht2D_MoveForward>(-700.0f, 1124.0f);

            // 被撃墜の煙のコンポーネント
            tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
                .spriteMaterialId(SpriteId::Spark)
                .generateLocalPosRandomRange({ 48.0f, 48.0f })
                .generateIntervalTimeSec(0.1f)
                .generateNumPerOnce(1)
                .totalGenerateNum(-1)
                .spriteBlendRate({ 1.0f, 0.5f })
                .setChild(false)
                .lifeTimeSec(1.0f)
                .moveSpeedPerSec(1024.0f)
                .spriteScale(0.6f)
                .spriteBlendRate({ 0.2f, 0.6f })
                .minGenerateAngleDeg(170.0f)
                .maxGenerateAngleDeg(190.0f)
                .blendRateChangeWidthPerSec({ 0.0f, -1.0f })
                .create();

            // 爆発のスプライトアニメーションを複数生成するコンポーネント
            tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
                .generateLocalPosRandomRange({ 128.0f, 128.0f })
                .generateIntervalTimeSec(0.2f)
                .generateNumPerOnce(1)
                .totalGenerateNum(10U)
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

tktk::GameObjectPtr Sht2D_Player::create(const tktkMath::Vector2& position)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // プレイヤーを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::Player);

    // プレイヤーの攻撃範囲であることを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::PlayerAttackRange);

    // ステートマシンを使用する準備を行う
    tktk::StateMachineListInitParam stateInitParam{};

    // 大元のステートは「生存」と「死亡」のどちらか
    stateInitParam.initRootNode({ PlayerStateType::Alive, PlayerStateType::Dead });

    // ステートマシンの初期化を行う
    gameObject->setupStateMachine(stateInitParam);

    // 最初は生存ステート
    gameObject->statesEnable({ PlayerStateType::Alive });

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .create();

    // 二次元慣性移動コンポーネント
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(1024.0f)
        .create();

    // スプライト描画コンポーネント
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Player)
        .create();

    // 接触時のダメージ
    gameObject->createComponent<Sht2D_DamagePower>(0.0f, 20.0f);

    // プレイヤー耐久力のコンポーネント
    gameObject->createComponent<Sht2D_HealthPoint>(100.0f);

    // プレイヤー弾数コンポーネント
    gameObject->createComponent<Sht2D_PlayerBulletCount>();

    // プレイヤーの衝突判定リアクションコンポーネント
    gameObject->createComponent<Sht2D_PlayerCollisionReaction>();

    // 生存ステートの準備をする
    setupAliveState(gameObject);

    // 死亡ステートの準備をする
    setupDeadState(gameObject);

    return gameObject;
}