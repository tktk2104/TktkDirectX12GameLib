#include "Act3D_FighterEnemy.h"

#include "../../../Enums/Enums.h"
#include "../../_CommonScripts/GravityMove/Act3D_GravityMove.h"

#include "../_CommonEnemyScripts/Act3D_RotateToPlayer.h"
#include "../_CommonEnemyScripts/Act3D_MoveForward.h"
#include "../_CommonEnemyScripts/Act3D_EnemyAttackRangeGenerator.h"
#include "../_CommonEnemyScripts/Act3D_EnemyJampAttackMoving.h"
#include "../_CommonEnemyScripts/Act3D_EnemyCollisionReaction.h"

#include "Scripts/Act3D_FighterEnemyParam.h"
#include "Scripts/Act3D_FighterEnemyDamager.h"
#include "Scripts/Act3D_FighterEnemyStartRun.h"
#include "Scripts/Act3D_FighterEnemyStartChase.h"
#include "Scripts/Act3D_FighterEnemyStartAttack.h"
#include "Scripts/Act3D_FighterEnemyStartComboAttack.h"
#include "Scripts/Act3D_FighterEnemyEndAttack.h"
#include "Scripts/Act3D_FighterEnemyEndDamage.h"

// 待機状態の設定を行う
inline void setFighterEnemyIdleState(tktk::GameObjectPtr gameObject)
{
    // 待機状態に追加する設定を行う
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Idle });
    {
        // プレイヤーとの位置関係によって歩き状態に遷移するコンポーネント
        gameObject->createComponent<Act3D_FighterEnemyStartChase>();

        // エネミーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_FighterEnemyDamager>();

        // アイドルモーションを開始する
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::FighterEnemyIdle).create();
    }
    // 待機状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// 移動状態の設定を行う
inline void setFighterEnemyMoveState(tktk::GameObjectPtr gameObject)
{
    // 移動状態に追加する設定を行う
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Move });
    {
        // プレイヤーの方へ向くコンポーネント
        gameObject->createComponent<Act3D_RotateToPlayer>(60.0f);

        // プレイヤーとの位置関係によって攻撃状態に遷移させる
        gameObject->createComponent<Act3D_FighterEnemyStartAttack>();

        // エネミーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_FighterEnemyDamager>();
    }

    // 歩き状態に追加する設定を行う
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Move, FighterEnemyState::Walk });
    {
        // 前方に進むコンポーネント（歩き状態）
        gameObject->createComponent<Act3D_MoveForward>(1.0f);

        // ３秒後に歩きから走りに移行する処理を設定する
        gameObject->createComponent<Act3D_FighterEnemyStartRun>();

         // 歩きモーションを開始する
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::FighterEnemyWalk).lerpTimeSec(0.1f).create();
    }

    // 走り状態に追加する設定を行う
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Move, FighterEnemyState::Run });
    {
        // 前方に進むコンポーネント（走り状態）
        gameObject->createComponent<Act3D_MoveForward>(1.5f);

        // 走りモーションを開始する
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::FighterEnemyRun).lerpTimeSec(0.5f).create();
    }

    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// 攻撃状態の設定を行う
inline void setFighterEnemyAttackState(tktk::GameObjectPtr gameObject)
{
    // ジャンプ攻撃状態に追加する設定を行う
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Attack, FighterEnemyState::JumpAttack });
    {
        // ジャンプ攻撃による移動のコンポーネント
        gameObject->createComponent<Act3D_EnemyJampAttackMoving>(4.0f, 1.8f);

        // ３秒後にジャンプ攻撃から歩き状態に移行する処理を設定する
        gameObject->createComponent<Act3D_FighterEnemyEndAttack>(3.0f, FighterEnemyState::JumpAttack);

        // ジャンプ攻撃の攻撃範囲を出現させるコンポーネント
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(1.2f, 2.8f, tktkMath::Vector3(0.0f, 1.0f, 0.5f), tktkMath::Vector3(2.0f, 1.0f, 2.0f));

        // ジャンプアタックモーションを開始する
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::FighterEnemyJumpAttack).isLoop(false).lerpTimeSec(0.5f).create();
    }

    // パンチ攻撃状態に追加する設定を行う
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Attack, FighterEnemyState::Punch });
    {
        // １秒後にパンチからスワイプに移行する処理を設定する
        gameObject->createComponent<Act3D_FighterEnemyStartComboAttack>();

         // エネミーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_FighterEnemyDamager>();
    
        // パンチの攻撃範囲を出現させるコンポーネント
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(0.2f, 0.8f, tktkMath::Vector3(0.0f, 1.0f, 0.6f), tktkMath::Vector3(2.0f, 1.0f, 1.0f));

        // パンチモーションを開始する
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::FighterEnemyPunch).isLoop(false).lerpTimeSec(0.5f).create();
    }

    // スワイプ攻撃状態に追加する設定を行う
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Attack, FighterEnemyState::Swiping });
    {
        // ２秒後にスワイプから歩き状態に移行する処理を設定する
        gameObject->createComponent<Act3D_FighterEnemyEndAttack>(2.0f, FighterEnemyState::Swiping);

        // エネミーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_FighterEnemyDamager>();

        // スワイプの攻撃範囲を出現させるコンポーネント
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(1.2f, 1.8f, tktkMath::Vector3(0.0f, 1.0f, 1.0f), tktkMath::Vector3(1.0f, 1.0f, 2.0f));

        // スワイプモーションを開始する
        tktk::MotionChangerMaker::makeStart( gameObject).initMotionId(MotionId::FighterEnemySwiping).isLoop(false).lerpTimeSec(0.5f).create();
    }

    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// 通常状態の設定を行う
inline void setFighterEnemyNormalState(tktk::GameObjectPtr gameObject)
{
    // 待機状態の設定を行う
    setFighterEnemyIdleState(gameObject);

    // 移動状態の設定を行う
    setFighterEnemyMoveState(gameObject);

    // 攻撃状態の設定を行う
    setFighterEnemyAttackState(gameObject);
}

// ダメージ状態の設定を行う
inline void setFighterEnemyDamageState(tktk::GameObjectPtr gameObject)
{
    // ダメージ状態に追加する設定を行う
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Damage });
    {
        // ダメージステートを終了する処理
        gameObject->createComponent<Act3D_FighterEnemyEndDamage>();

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
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::FighterEnemyDamage).initFrame(5.0f).lerpTimeSec(0.1f).isLoop(false).create();
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// 生存状態の設定を行う
inline void setFighterEnemyAliveState(tktk::GameObjectPtr gameObject)
{
    // 生存状態に追加する設定を行う
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive });
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
    setFighterEnemyNormalState(gameObject);

    // ダメージ状態の設定を行う
    setFighterEnemyDamageState(gameObject);
}

// 死亡状態の設定を行う
inline void setFighterEnemyDeadState(tktk::GameObjectPtr gameObject)
{
    // 死亡状態に追加する設定を行う
    gameObject->setTargetHierarchy({ FighterEnemyState::Dead });
    {
        // 死亡モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::FighterEnemyDead).initFrame(20.0f).lerpTimeSec(0.1f).isLoop(false).create();
    
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

tktk::GameObjectPtr Act3D_FighterEnemy::create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation)
{
    // ゲームオブジェクトを作成
    auto gameObject = tktk::DX12Game::createGameObject();

    // エネミータグを追加
    gameObject->addGameObjectTag(GameObjectTag::Enemy);

    // ステートマシンを使用する準備を行う
    tktk::StateMachineListInitParam initParam{};

    // 大元のステートは「生存」か「死亡」のどちらか
    initParam.initRootNode({ FighterEnemyState::Alive, FighterEnemyState::Dead });

    // 「生存ステート」は「通常」と「ダメージ」の２つのステートから成り立っている
    initParam.addChildNode({ FighterEnemyState::Alive }, { FighterEnemyState::Normal, FighterEnemyState::Damage });

    // 「生存・通常ステート」には「待機」「移動」「攻撃」の３つのステートから成り立っている
    initParam.addChildNode({ FighterEnemyState::Alive, FighterEnemyState::Normal },
        { FighterEnemyState::Idle, FighterEnemyState::Move, FighterEnemyState::Attack });

    // 「生存・通常・移動ステート」には「歩き」「走り」の２つのステートから成り立っている
    initParam.addChildNode({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Move },
        { FighterEnemyState::Walk,  FighterEnemyState::Run });

    // 「生存・通常・攻撃ステート」には「パンチ」「スワイプ」「ジャンプ攻撃」の３つのステートから成り立っている
    initParam.addChildNode({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Attack },
        { FighterEnemyState::Punch, FighterEnemyState::Swiping, FighterEnemyState::JumpAttack });

    // ステートマシンの初期化
    gameObject->setupStateMachine(initParam);

    // 最初は「生存・通常・待機ステート」
    gameObject->statesEnable({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Idle });

    // 生存状態の設定を行う
    setFighterEnemyAliveState(gameObject);

    // 死亡状態の設定を行う
    setFighterEnemyDeadState(gameObject);

    // ３次元座標コンポーネント
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotation(rotation)
        .create();

    // メッシュ描画コンポーネント
    tktk::MeshDrawerMaker::makeStart(gameObject)
        .meshId(BasicMeshId::FighterEnemy)
        .skeletonId(SkeletonId::FighterEnemy)
        .baseScale(0.1f)
        .baseRotation(tktkMath::Quaternion::createFromEulerAngle({ 0.0f, 180.0f, 0.0f }))
        .create();

    // メッシュのアニメーションコンポーネント
    tktk::MeshAnimatorMaker::makeStart(gameObject)
        .initMotionId(MotionId::FighterEnemyIdle)
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
    gameObject->createComponent<Act3D_FighterEnemyParam>();

    return gameObject;
}