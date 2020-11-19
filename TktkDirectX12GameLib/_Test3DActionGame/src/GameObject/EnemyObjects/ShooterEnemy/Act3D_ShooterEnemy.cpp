#include "Act3D_ShooterEnemy.h"

#include "../../../Enums/Enums.h"
#include "../../_CommonScripts/GravityMove/Act3D_GravityMove.h"

#include "../_CommonEnemyScripts/Act3D_RotateToPlayer.h"
#include "../_CommonEnemyScripts/Act3D_MoveForward.h"
#include "../_CommonEnemyScripts/Act3D_EnemyAttackRangeGenerator.h"
#include "../_CommonEnemyScripts/Act3D_EnemyJampAttackMoving.h"
#include "../_CommonEnemyScripts/Act3D_EnemyCollisionReaction.h"

#include "Scripts/Act3D_ShooterEnemyParam.h"
#include "Scripts/Act3D_ShooterEnemyStartChase.h"
#include "Scripts/Act3D_ShooterEnemyStartAttack.h"
#include "Scripts/Act3D_ShooterEnemyBulletGenerator.h"
#include "Scripts/Act3D_ShooterEnemyEndAttack.h"
#include "Scripts/Act3D_ShooterEnemyEndDamage.h"
#include "Scripts/Act3D_ShooterEnemyDamager.h"

// 待機状態の設定を行う
inline void createShooterEnemyIdleSetting(tktk::GameObjectPtr gameObject)
{
    // 待機状態に追加する設定を行う
    gameObject->setTargetHierarchy({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Normal, ShooterEnemyStateType::Idle });
    {
        // プレイヤーとの位置関係によって移動状態に遷移するコンポーネント
        gameObject->createComponent<Act3D_ShooterEnemyStartChase>();

        // エネミーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_ShooterEnemyDamager>();

        // アイドルモーションを開始する
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::ShooterEnemyIdle).create();
    }
    // 待機状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// 移動状態の設定を行う
inline void createShooterEnemyMoveSetting(tktk::GameObjectPtr gameObject)
{
    // 移動状態に追加する設定を行う
    gameObject->setTargetHierarchy({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Normal, ShooterEnemyStateType::Move });
    {
        // プレイヤーの方へ向くコンポーネント
        gameObject->createComponent<Act3D_RotateToPlayer>(60.0f);

        // 前方に進むコンポーネント（歩き状態）
        gameObject->createComponent<Act3D_MoveForward>(0.5f);

        // プレイヤーとの位置関係によって攻撃状態に遷移させる
        gameObject->createComponent<Act3D_ShooterEnemyStartAttack>();

        // エネミーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_ShooterEnemyDamager>();

        // 歩きモーションを開始する
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::ShooterEnemyWalk).lerpTimeSec(0.1f).create();
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// 攻撃状態の設定を行う
inline void createShooterEnemyAttackSetting(tktk::GameObjectPtr gameObject)
{
    // 近距離攻撃状態に追加する設定を行う
    gameObject->setTargetHierarchy({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Normal, ShooterEnemyStateType::Attack, ShooterEnemyStateType::Attack_1 });
    {
        // 2.2秒後に近距離攻撃から歩き状態に移行する処理を設定する
        gameObject->createComponent<Act3D_ShooterEnemyEndAttack>(2.2f, ShooterEnemyStateType::Attack_1);

        // エネミーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_ShooterEnemyDamager>();

        // パンチの攻撃範囲を出現させるコンポーネント
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(1.5f, 2.0f, tktkMath::Vector3(0.0f, 1.0f, 0.6f), tktkMath::Vector3(1.0f, 1.0f, 1.0f));

        // パンチモーションを開始する
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::ShooterEnemyAttack).isLoop(false).lerpTimeSec(0.5f).create();
    }

    // 遠距離攻撃状態に追加する設定を行う
    gameObject->setTargetHierarchy({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Normal, ShooterEnemyStateType::Attack, ShooterEnemyStateType::Shot });
    {
        // プレイヤーの方へ向くコンポーネント
        gameObject->createComponent<Act3D_RotateToPlayer>(60.0f);

        // ２秒後に遠距離攻撃から歩き状態に移行する処理を設定する
        gameObject->createComponent<Act3D_ShooterEnemyEndAttack>(2.0f, ShooterEnemyStateType::Shot);

        // エネミーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_ShooterEnemyDamager>();

        // 弾発射コンポーネント
        gameObject->createComponent<Act3D_ShooterEnemyBulletGenerator>();

        // スワイプモーションを開始する
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::ShooterEnemyShot).isLoop(false).lerpTimeSec(0.5f).create();
    }

    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// 通常状態の設定を行う
inline void setShooterEnemyNormalState(tktk::GameObjectPtr gameObject)
{
    // 待機状態の設定を行う
    createShooterEnemyIdleSetting(gameObject);

    // 移動状態の設定を行う
    createShooterEnemyMoveSetting(gameObject);

    // 攻撃状態の設定を行う
    createShooterEnemyAttackSetting(gameObject);
}

// ダメージ状態の設定を行う
inline void setShooterEnemyDamageState(tktk::GameObjectPtr gameObject)
{
    // ダメージ状態に追加する設定を行う
    gameObject->setTargetHierarchy({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Damage });
    {
        // ダメージステートを終了する処理
        gameObject->createComponent<Act3D_ShooterEnemyEndDamage>();

        // 拡散するビルボードパーティクルコンポーネント
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 1.0f, 0.4f, 0.0f, 1.0f }) // 黄色
            .generateLocalPos({ 0.0f, 1.0f, 0.0f })
            .generateLocalPosRandomRange({ 0.5f, 0.5f, 0.5f })
            .lifeTimeSec(0.4f)
            .generateNumPerOnce(30)
            .totalGenerateNum(30)
            .changeAvtiveToReset(true)
            .create();

        // ダメージモーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::ShooterEnemyDamage).lerpTimeSec(0.1f).isLoop(false).create();
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// 生存状態の設定を行う
inline void setShooterEnemyAliveState(tktk::GameObjectPtr gameObject)
{
    // 生存状態に追加する設定を行う
    gameObject->setTargetHierarchy({ ShooterEnemyStateType::Alive });
    {
        // ３次元慣性移動コンポーネント
        tktk::InertialMovement3DMaker::makeStart(gameObject)
            .decelerationPerSec(1.0f)
            .craete();

        // OBB衝突判定コンポーネント
        tktk::BoxColliderMaker::makeStart(gameObject)
            .boxSize({ 1.0f, 2.0f, 1.0f })
            .localPosition({ 0.0f, 1.0f, 0.0f })
            .collisionGroupType(CollisionGroup::Enemy)
            .extrudedRate(0.5f)
            .isExtrude(true)
            .create();

        // エネミーの衝突判定のリアクション
        gameObject->createComponent<Act3D_EnemyCollisionReaction>();

        // 重力による移動コンポーネント
        gameObject->createComponent<Act3D_GravityMove>(3.0f);
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});

    // 通常状態の設定を行う
    setShooterEnemyNormalState(gameObject);

    // ダメージ状態の設定を行う
    setShooterEnemyDamageState(gameObject);
}

// 死亡状態の設定を行う
inline void setShooterEnemyDeadState(tktk::GameObjectPtr gameObject)
{
    // 死亡状態に追加する設定を行う
    gameObject->setTargetHierarchy({ ShooterEnemyStateType::Dead });
    {
        // 死亡モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::ShooterEnemyDead).initFrame(30.0f).lerpTimeSec(0.1f).isLoop(false).create();

        // 拡散するビルボードパーティクルコンポーネント
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 1.0f, 0.4f, 0.0f, 1.0f }) // 黄色
            .generateLocalPos({ 0.0f, 1.0f, 0.0f })
            .generateLocalPosRandomRange({ 0.5f, 0.5f, 0.5f })
            .lifeTimeSec(0.4f)
            .generateNumPerOnce(30)
            .totalGenerateNum(30)
            .changeAvtiveToReset(true)
            .create();
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

tktk::GameObjectPtr Act3D_ShooterEnemy::create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation)
{
    // ゲームオブジェクトを作成
    auto gameObject = tktk::DX12Game::createGameObject();

    // エネミータグを追加
    gameObject->addGameObjectTag(GameObjectTag::Enemy);

    // ステートマシンを使用する準備を行う
    tktk::StateMachineListInitParam initParam{};

    // 大元のステートは「生存」か「死亡」のどちらか
    initParam.initRootNode({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Dead });

    // 「生存ステート」は「通常」と「ダメージ」の２つのステートから成り立っている
    initParam.addChildNode({ ShooterEnemyStateType::Alive }, { ShooterEnemyStateType::Normal, ShooterEnemyStateType::Damage });

    // 「生存・通常ステート」には「待機」「移動」「攻撃」の３つのステートから成り立っている
    initParam.addChildNode({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Normal },
        { ShooterEnemyStateType::Idle, ShooterEnemyStateType::Move, ShooterEnemyStateType::Attack });

    // 「生存・通常・攻撃ステート」には「パンチ」「スワイプ」「ジャンプ攻撃」の３つのステートから成り立っている
    initParam.addChildNode({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Normal, ShooterEnemyStateType::Attack },
        { ShooterEnemyStateType::Attack_1, ShooterEnemyStateType::Shot });

    // ステートマシンの初期化
    gameObject->setupStateMachine(initParam);

    // 最初は「生存・通常・待機ステート」
    gameObject->statesEnable({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Normal, ShooterEnemyStateType::Idle });

    // 生存状態の設定を行う
    setShooterEnemyAliveState(gameObject);

    // 死亡状態の設定を行う
    setShooterEnemyDeadState(gameObject);

    // ３次元座標コンポーネント
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotation(rotation)
        .create();

    // メッシュ描画コンポーネント
    tktk::MeshDrawerMaker::makeStart(gameObject)
        .meshId(BasicMeshId::ShooterEnemy)
        .skeletonId(SkeletonId::ShooterEnemy)
        .baseScale(0.1f)
        .baseRotation(tktkMath::Quaternion::createFromEulerAngle({ 0.0f, 180.0f, 0.0f }))
        .create();

    // メッシュのアニメーションコンポーネント
    tktk::MeshAnimatorMaker::makeStart(gameObject)
        .initMotionId(MotionId::ShooterEnemyIdle)
        .isLoop(true)
        .animFramePerSec(30.0f)
        .create();

// 衝突判定範囲描画コンポーネント
#ifdef _DEBUG
    tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::red)
        .create();
#endif // _DEBUG

    // エネミーの能力値
    gameObject->createComponent<Act3D_ShooterEnemyParam>();

    return gameObject;
}
