#include "Act3D_Player.h"

#include "../../../Enums/Enums.h"
#include "../../CameraObjects/DefaultCamera/Act3D_DefaultCamera.h"

#include "Scripts/Act3D_PlayerController.h"
#include "Scripts/Act3D_InputToStartAttack.h"
#include "Scripts/Act3D_InputToStartComboAttack.h"
#include "Scripts/Act3D_JampAttackMoving.h"
#include "Scripts/Act3D_PlayerAttackRangeGenerator.h"
#include "Scripts/Act3D_PlayerCollisionReaction.h"
#include "Scripts/Act3D_PlayerDamager.h"
#include "Scripts/Act3D_PlayerEndAttack.h"
#include "Scripts/Act3D_PlayerEndDamage.h"

#include "../../_CommonScripts/GravityMove/Act3D_GravityMove.h"

// 移動状態の設定を行う
inline void createPlayerMoveSetting(tktk::GameObjectPtr gameObject)
{
    // 移動状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Move });
    {
        // プレイヤー移動兼、移動ステート変更コンポーネント
        gameObject->createComponent<Act3D_PlayerController>(2.0f, 45.0f);

        // 攻撃開始を行うコンポーネント
        gameObject->createComponent<Act3D_InputToStartAttack>();

        // プレイヤーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_PlayerDamager>();
    }

    // 待機状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::Idle });
    {
        // 待機モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerIdle).lerpTimeSec(0.3f).create();
    }

    // 前方歩き状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::WalkForward });
    {
        // 前方歩き移動モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkForward).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();
    }

    // 後方歩き状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::WalkBackward });
    {
        // 後方歩き移動モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkBackward).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();
    }

    // 左歩き状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Normal,  PlayerStateType::Move, PlayerStateType::WalkLeft });
    {
        // 左歩き移動モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkLeft).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();
    }

    // 右歩き状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::WalkRight });
    {
        // 右歩き移動モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkRight).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();
    }

    // 前方走り状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::RunForward });
    {
        // 前方走り移動モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerRunForward).lerpTimeSec(0.2f).motionSpeedRate(1.5f).create();
    }

    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// 攻撃状態の設定を行う
inline void createPlayerAttackSetting(tktk::GameObjectPtr gameObject)
{
    // 攻撃（１段）状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Attack, PlayerStateType::Attack1 });
    {
        // 攻撃（１段）の攻撃範囲を出現させるコンポーネント
        gameObject->createComponent<Act3D_PlayerAttackRangeGenerator>(0.1f, 0.3f, tktkMath::Vector3(0.0f, 1.0f, 0.6f), tktkMath::Vector3(1.0f, 1.0f, 1.0f));

        // １段目から２段目の攻撃に遷移するコンポーネント
        gameObject->createComponent<Act3D_InputToStartComboAttack>(0.3f);

        // 攻撃（１段）モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerAttack1).initFrame(15.0f).lerpTimeSec(0.1f).isLoop(false).motionSpeedRate(2.0f).create();

        // 攻撃ステートを終了するコンポーネント
        gameObject->createComponent<Act3D_PlayerEndAttack>(0.5f, PlayerStateType::Attack1);

        // プレイヤーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_PlayerDamager>();
    }

    // 攻撃（２段）状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Attack, PlayerStateType::Attack2 });
    {
        // 攻撃（２段）の攻撃範囲を出現させるコンポーネント
        gameObject->createComponent<Act3D_PlayerAttackRangeGenerator>(0.2f, 0.5f, tktkMath::Vector3(0.0f, 1.0f, 0.6f), tktkMath::Vector3(2.0f, 1.0f, 1.0f));

        // 攻撃（２段）モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerAttack2).initFrame(15.0f).lerpTimeSec(0.1f).isLoop(false).motionSpeedRate(1.5f).create();

        // 攻撃ステートを終了するコンポーネント
        gameObject->createComponent<Act3D_PlayerEndAttack>(0.8f, PlayerStateType::Attack2);

        // プレイヤーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_PlayerDamager>();
    }

    // ジャンプ攻撃状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Attack, PlayerStateType::JumpAttack });
    {
        // ジャンプ攻撃の攻撃範囲を出現させるコンポーネント
        gameObject->createComponent<Act3D_PlayerAttackRangeGenerator>(1.0f, 2.0f, tktkMath::Vector3(0.0f, 1.0f, 0.5f), tktkMath::Vector3(1.0f, 1.0f, 2.0f));

        // ジャンプ攻撃による移動のコンポーネント
        gameObject->createComponent<Act3D_JampAttackMoving>(5.0f, 1.3f);

        // 収縮するビルボードパーティクルコンポーネント
        tktk::BillboardShrinkEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate(tktkMath::Color_v::blue)
            .shrinkTargetPos({ 0.0f, 1.0f, 0.0f })
            .totalGenerateNum(20)
            .setChild(true)
            .changeAvtiveToReset(true)
            .create();

        // ジャンプ攻撃モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerJumpAttack).initFrame(20.0f).lerpTimeSec(0.1f).isLoop(false).create();

        // 攻撃ステートを終了するコンポーネント
        gameObject->createComponent<Act3D_PlayerEndAttack>(2.0f, PlayerStateType::JumpAttack);
    }
   
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// ダメージ状態の設定を行う
inline void createDamageAttackSetting(tktk::GameObjectPtr gameObject)
{
    // 攻撃（１段）状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Damage });

    // ダメージステートを終了する処理
    gameObject->createComponent<Act3D_PlayerEndDamage>();

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
    tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerDamage).initFrame(10.0f).lerpTimeSec(0.1f).isLoop(false).create();

    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

tktk::GameObjectPtr Act3D_Player::create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation)
{
    // ゲームオブジェクトを作成
    auto gameObject = tktk::DX12Game::createGameObject();

    // プレイヤータグを追加
    gameObject->addGameObjectTag(GameObjectTag::Player);

    // ステートマシンを使用する準備を行う
    tktk::StateMachineListInitParam initParam{};
    initParam.initRootNode({
            PlayerStateType::Normal,
            PlayerStateType::Damage,
            PlayerStateType::Dead
        });
    initParam.addChildNode({ PlayerStateType::Normal }, {
           PlayerStateType::Move,
           PlayerStateType::Attack
        });
    initParam.addChildNode({ PlayerStateType::Normal, PlayerStateType::Move }, {
            PlayerStateType::Idle,
            PlayerStateType::WalkForward,
            PlayerStateType::WalkBackward,
            PlayerStateType::WalkLeft,
            PlayerStateType::WalkRight,
            PlayerStateType::RunForward
        });
    initParam.addChildNode({ PlayerStateType::Normal, PlayerStateType::Attack },{
            PlayerStateType::Attack1,
            PlayerStateType::Attack2,
            PlayerStateType::JumpAttack
        });
    gameObject->setupStateMachine(initParam);

    // 最初は移動ステート
    gameObject->stateEnable(PlayerStateType::Normal);
    gameObject->stateEnable(PlayerStateType::Move);

    // 移動状態の設定を行う
    createPlayerMoveSetting(gameObject);

    // 攻撃状態の設定を行う
    createPlayerAttackSetting(gameObject);

    // ダメージ状態の設定を行う
    createDamageAttackSetting(gameObject);

    // ３次元座標コンポーネント
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotation(rotation)
        .create();

    // ３次元慣性移動コンポーネント
    tktk::InertialMovement3DMaker::makeStart(gameObject)
        .decelerationPerSec(1.0f)
        .craete();

    // メッシュ描画コンポーネント
    tktk::MeshDrawerMaker::makeStart(gameObject)
        .meshId(BasicMeshId::Player)
        .skeletonId(SkeletonId::Player)
        .baseScale(0.1f)
        .baseRotation(tktkMath::Quaternion::createFromEulerAngle({ 0.0f, 180.0f, 0.0f }))
        .create();

    // メッシュのアニメーションコンポーネント
    tktk::MeshAnimatorMaker::makeStart(gameObject)
        .initMotionId(MotionId::PlayerIdle)
        .isLoop(true)
        .animFramePerSec(30.0f)
        .create();

    // OBB衝突判定コンポーネント
    tktk::BoxColliderMaker::makeStart(gameObject)
        .boxSize({ 0.8f, 1.6f, 0.8f })
        .localPosition({ 0.0f, 0.8f, 0.0f })
        .collisionGroupType(CollisionGroup::Player)
        .isExtrude(true)
        .extrudedRate(1.0f)
        .create();

// 衝突判定範囲描画コンポーネント
#ifdef _DEBUG
    tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::blue)
        .create();
#endif // _DEBUG

    // プレイヤーの衝突判定のリアクション
    gameObject->createComponent<Act3D_PlayerCollisionReaction>();

    // 重力による移動コンポーネント
    gameObject->createComponent<Act3D_GravityMove>(3.0f);

    // カメラを自身の子供に設定する
    gameObject->addChild(Act3D_DefaultCamera::create({ 0.0f, 3.0f, -3.0f }, tktkMath::Quaternion::createLookRotation({ 0.0f, -2.0f, 3.0f })));

    return gameObject;
}
