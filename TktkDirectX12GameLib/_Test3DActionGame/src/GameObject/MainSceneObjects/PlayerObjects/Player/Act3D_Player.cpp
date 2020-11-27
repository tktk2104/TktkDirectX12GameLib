#include "Act3D_Player.h"

#include "../../../../Enums/Enums.h"

#include "Scripts/Act3D_PlayerController.h"
#include "Scripts/Act3D_InputToStartAttack.h"
#include "Scripts/Act3D_InputToStartComboAttack.h"
#include "Scripts/Act3D_InputToStartDodge.h"
#include "Scripts/Act3D_JampAttackMoving.h"
#include "Scripts/Act3D_PlayerAttackRangeGenerator.h"
#include "Scripts/Act3D_PlayerCollisionReaction.h"
#include "Scripts/Act3D_PlayerDamager.h"
#include "Scripts/Act3D_PlayerEndAttack.h"
#include "Scripts/Act3D_PlayerEndDodge.h"
#include "Scripts/Act3D_PlayerEndDamage.h"
#include "Scripts/Act3D_PlayerParam.h"

#include "../../../_CommonScripts/GravityMove/Act3D_GravityMove.h"

#include "../../../SkyBox/Act3D_SkyBox.h"

// 移動状態の設定を行う
inline void setPlayerMoveState(tktk::GameObjectPtr gameObject)
{
    // 移動状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move });
    {
        // プレイヤー移動兼、移動ステート変更コンポーネント
        gameObject->createComponent<Act3D_PlayerController>(2.0f, 75.0f);

        // 攻撃開始を行うコンポーネント
        gameObject->createComponent<Act3D_InputToStartAttack>();

        // 回避開始を行うコンポーネント
        gameObject->createComponent<Act3D_InputToStartDodge>();

        // プレイヤーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_PlayerDamager>();
    }

    // 待機状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::Idle });
    {
        // 待機モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerIdle).lerpTimeSec(0.3f).create();
    }

    // 前方歩き状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::WalkForward });
    {
        // 前方歩き移動モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkForward).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerWalk)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.15f)
            .playIntervalSec(0.28f)
            .playCount(-1)
            .create();
    }

    // 後方歩き状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::WalkBackward });
    {
        // 後方歩き移動モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkBackward).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();
    
        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerWalk)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.15f)
            .playIntervalSec(0.31f)
            .playCount(-1)
            .create();
    }

    // 左歩き状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal,  PlayerStateType::Move, PlayerStateType::WalkLeft });
    {
        // 左歩き移動モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkLeft).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();
    
        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerWalk)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.15f)
            .playIntervalSec(0.26f)
            .playCount(-1)
            .create();
    }

    // 右歩き状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::WalkRight });
    {
        // 右歩き移動モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkRight).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();
    
        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerWalk)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.15f)
            .playIntervalSec(0.27f)
            .playCount(-1)
            .create();
    }

    // 前方走り状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::RunForward });
    {
        // 前方走り移動モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerRunForward).lerpTimeSec(0.2f).motionSpeedRate(1.5f).create();
    
        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerRun)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playIntervalSec(0.13f)
            .playCount(-1)
            .create();
    }

    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// 攻撃状態の設定を行う
inline void setPlayerAttackState(tktk::GameObjectPtr gameObject)
{
    // 攻撃（１段）状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Attack, PlayerStateType::Attack1 });
    {
        // 攻撃（１段）の攻撃範囲を出現させるコンポーネント
        gameObject->createComponent<Act3D_PlayerAttackRangeGenerator>(0.1f, 0.3f, tktkMath::Vector3(0.0f, 1.0f, 0.6f), tktkMath::Vector3(1.0f, 1.0f, 1.0f));

        // １段目から２段目の攻撃に遷移するコンポーネント
        gameObject->createComponent<Act3D_InputToStartComboAttack>();

        // 攻撃（１段）モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerAttack1).initFrame(15.0f).lerpTimeSec(0.1f).isLoop(false).motionSpeedRate(2.0f).create();

        // 攻撃ステートを終了するコンポーネント
        gameObject->createComponent<Act3D_PlayerEndAttack>(0.5f);

        // プレイヤーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_PlayerDamager>();

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerAttack1)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::LightSword)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.1f)
            .playCount(1)
            .create();
    }

    // 攻撃（２段）状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Attack, PlayerStateType::Attack2 });
    {
        // 攻撃（２段）の攻撃範囲を出現させるコンポーネント
        gameObject->createComponent<Act3D_PlayerAttackRangeGenerator>(0.2f, 0.5f, tktkMath::Vector3(0.0f, 1.0f, 0.6f), tktkMath::Vector3(2.0f, 1.0f, 1.0f));

        // 攻撃（２段）モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerAttack2).initFrame(15.0f).lerpTimeSec(0.1f).isLoop(false).motionSpeedRate(1.5f).create();

        // 攻撃ステートを終了するコンポーネント
        gameObject->createComponent<Act3D_PlayerEndAttack>(0.8f);

        // プレイヤーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_PlayerDamager>();

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerAttack2)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::MiddleSword)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.2f)
            .playCount(1)
            .create();
    }

    // ジャンプ攻撃状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Attack, PlayerStateType::JumpAttack });
    {
        // ジャンプ攻撃の攻撃範囲を出現させるコンポーネント
        gameObject->createComponent<Act3D_PlayerAttackRangeGenerator>(1.0f, 2.0f, tktkMath::Vector3(0.0f, 1.0f, 0.5f), tktkMath::Vector3(1.0f, 1.0f, 2.0f));

        // ジャンプ攻撃による移動のコンポーネント
        gameObject->createComponent<Act3D_JampAttackMoving>();

        // 収縮するビルボードパーティクルコンポーネント
        tktk::BillboardShrinkEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate(tktkMath::Color_v::blue)
            .shrinkTargetPos({ 0.0f, 1.0f, 0.0f })
            .totalGenerateNum(20)
            .setChild(true)
            .changeAvtiveToReset(true)
            .create();

        // 拡散するビルボードパーティクルコンポーネント
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // グレー
            .generateLocalPos({ 0.0f, 0.5f, 0.0f })
            .generateLocalPosRandomRange({ 0.2f, 0.2f, 0.2f })
            .billboardScale({ 0.2f, 0.2f })
            .moveSpeedPerSec(1.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(10)
            .totalGenerateNum(30)
            .firstGenerateTimeSec(1.2f)
            .generateIntervalTimeSec(0.01f)
            .changeAvtiveToReset(true)
            .create();

        // 拡散するビルボードパーティクルコンポーネント
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // グレー
            .generateLocalPos({ 0.0f, 0.0f, 0.0f })
            .generateLocalPosRandomRange({ 0.2f, 0.2f, 0.2f })
            .moveSpeedPerSec(3.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(10)
            .totalGenerateNum(60)
            .firstGenerateTimeSec(1.2f)
            .generateIntervalTimeSec(0.02f)
            .changeAvtiveToReset(true)
            .create();

        // ジャンプ攻撃モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerJumpAttack).initFrame(20.0f).lerpTimeSec(0.1f).isLoop(false).create();

        // 攻撃ステートを終了するコンポーネント
        gameObject->createComponent<Act3D_PlayerEndAttack>(2.0f);

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerJumpAttack)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::HeavySword)
            .startToPlay(false)
            .firstPlayStartTimeSec(1.0f)
            .playCount(1)
            .create();

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::HeavyBlow)
            .startToPlay(false)
            .firstPlayStartTimeSec(1.0f)
            .playCount(1)
            .create();
    }
   
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// 通常状態の設定を行う
inline void setPlayerNormalState(tktk::GameObjectPtr gameObject)
{
    // 移動状態の設定を行う
    setPlayerMoveState(gameObject);

    // 攻撃状態の設定を行う
    setPlayerAttackState(gameObject);
}

// 回避状態の設定を行う
inline void setPlayerDodgeState(tktk::GameObjectPtr gameObject)
{
    // 回避状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Dodge });
    {
        // 回避ステートを終了する処理
        gameObject->createComponent<Act3D_PlayerEndDodge>();

        // 回避モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerDodge).initFrame(10.0f).lerpTimeSec(0.1f).isLoop(false).create();

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::LightBlow)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.5f)
            .playCount(1)
            .create();

        // 拡散するビルボードパーティクルコンポーネント
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // グレー
            .generateLocalPos({ 0.0f, 0.0f, 0.0f })
            .generateLocalPosRandomRange({ 0.2f, 0.2f, 0.2f })
            .moveSpeedPerSec(3.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(10)
            .generateIntervalTimeSec(0.1f)
            .changeAvtiveToReset(true)
            .create();
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// ダメージ状態の設定を行う
inline void setPlayerDamageState(tktk::GameObjectPtr gameObject)
{
    // ダメージ状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Damage });
    {
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

        // 拡散するビルボードパーティクルコンポーネント
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate(tktkMath::Color_v::red)
            .generateLocalPos({ 0.0f, 1.0f, 0.0f })
            .generateLocalPosRandomRange({ 0.5f, 0.5f, 0.5f })
            .lifeTimeSec(0.4f)
            .generateNumPerOnce(10)
            .totalGenerateNum(10)
            .moveSpeedPerSec(1.0f)
            .billboardScale(0.3f)
            .changeAvtiveToReset(true)
            .create();

        // ダメージモーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerDamage).initFrame(10.0f).lerpTimeSec(0.1f).isLoop(false).create();

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerDamage)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// 生存状態の設定を行う
inline void setPlayerAliveState(tktk::GameObjectPtr gameObject)
{
    // 生存状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Alive });
    {
        // ３次元慣性移動コンポーネント
        tktk::InertialMovement3DMaker::makeStart(gameObject)
            .decelerationPerSec(2.0f)
            .craete();

        // OBB衝突判定コンポーネント
        tktk::BoxColliderMaker::makeStart(gameObject)
            .boxSize({ 0.8f, 1.6f, 0.8f })
            .localPosition({ 0.0f, 0.8f, 0.0f })
            .collisionGroupType(CollisionGroup::Player)
            .isExtrude(true)
            .extrudedRate(1.0f)
            .create();

        // プレイヤーの衝突判定のリアクション
        gameObject->createComponent<Act3D_PlayerCollisionReaction>();

        // 重力による移動コンポーネント
        gameObject->createComponent<Act3D_GravityMove>();
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});

    // 通常状態の設定を行う
    setPlayerNormalState(gameObject);

    // 回避状態の設定を行う
    setPlayerDodgeState(gameObject);

    // ダメージ状態の設定を行う
    setPlayerDamageState(gameObject);
}

// 死亡状態の設定を行う
inline void setPlayerDeadState(tktk::GameObjectPtr gameObject)
{
    // 死亡状態に追加する設定を行う
    gameObject->setTargetHierarchy({ PlayerStateType::Dead });
    {
        // 死亡モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerDead).initFrame(10.0f).lerpTimeSec(0.1f).isLoop(false).create();

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

        // 拡散するビルボードパーティクルコンポーネント
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate(tktkMath::Color_v::red)
            .generateLocalPos({ 0.0f, 1.0f, 0.0f })
            .generateLocalPosRandomRange({ 0.5f, 0.5f, 0.5f })
            .lifeTimeSec(0.4f)
            .generateNumPerOnce(10)
            .totalGenerateNum(10)
            .moveSpeedPerSec(1.0f)
            .billboardScale(0.3f)
            .changeAvtiveToReset(true)
            .create();

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerDead)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

tktk::GameObjectPtr Act3D_Player::create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation)
{
    // ゲームオブジェクトを作成
    auto gameObject = tktk::DX12Game::createGameObject();

    // メインシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::MainSceneObject);

    // プレイヤータグを追加
    gameObject->addGameObjectTag(GameObjectTag::Player);

    // ステートマシンを使用する準備を行う
    tktk::StateMachineListInitParam initParam{};

    // 大元のステートは「生存」と「死亡」のどちらか
    initParam.initRootNode({ PlayerStateType::Alive, PlayerStateType::Dead });

    // 「生存ステート」は「通常」と「回避」「ダメージ」の３つのステートから成り立っている
    initParam.addChildNode({ PlayerStateType::Alive }, { PlayerStateType::Normal, PlayerStateType::Dodge, PlayerStateType::Damage });

    // 「生存・通常ステート」は「移動」と「攻撃」の２つのステートから成り立っている
    initParam.addChildNode({ PlayerStateType::Alive, PlayerStateType::Normal }, { PlayerStateType::Move, PlayerStateType::Attack });

    // 「生存・通常・移動ステート」は「待機」と「前方走り」「各方位歩き」ステートから成り立っている
    initParam.addChildNode({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move }, {
            PlayerStateType::Idle,
            PlayerStateType::WalkForward,
            PlayerStateType::WalkBackward,
            PlayerStateType::WalkLeft,
            PlayerStateType::WalkRight,
            PlayerStateType::RunForward
        });

    // 「生存・通常・攻撃ステート」は「一段目攻撃」と「二段目攻撃」「ジャンプ攻撃」の３つのステートから成り立っている
    initParam.addChildNode({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Attack },{ PlayerStateType::Attack1, PlayerStateType::Attack2, PlayerStateType::JumpAttack });
    
    // ステートマシンの初期化を行う
    gameObject->setupStateMachine(initParam);

    // 最初は移動ステート
    gameObject->statesEnable({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move });

    // 生存状態の設定を行う
    setPlayerAliveState(gameObject);

    // 死亡状態の設定を行う
    setPlayerDeadState(gameObject);

    // ３次元座標コンポーネント
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotation(rotation)
        .create();

    // メッシュ描画コンポーネント
    tktk::MeshDrawerMaker::makeStart(gameObject)
        .meshId(MeshId::Player)
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

// 衝突判定範囲描画コンポーネント
#ifdef _DEBUG
    tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::blue)
        .create();
#endif // _DEBUG

    // プレイヤーの能力値
    gameObject->createComponent<Act3D_PlayerParam>();

    // カメラを自身の子供に設定する
    gameObject->addChild(createCamera({ 0.0f, 3.0f, -3.0f }, tktkMath::Quaternion::createLookRotation({ 0.0f, -1.0f, 3.0f })));

    return gameObject;
}

tktk::GameObjectPtr Act3D_Player::createCamera(const tktkMath::Vector3& position, const tktkMath::Quaternion& rotation)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // プレイヤーカメラタグを付ける
    gameObject->addGameObjectTag(GameObjectTag::PlayerCamera);

    // 座標管理コンポーネント
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotation(rotation)
        .create();

    // 通常カメラコンポーネント
    tktk::BasicCameraControllerMaker::makeStart(gameObject)
        .initCameraFov(90.0f)
        .create();

    // シャドウマップカメラコンポーネント
    tktk::ShadowMapCameraControllerMaker::makeStart(gameObject)
        .direction({ 0.0f, -1.0f, 1.0f })
        .initCameraWidth(50.0f)
        .initCameraHeight(50.0f)
        .initCameraNear(0.0f)
        .initCameraFar(100.0f)
        .targetTag(GameObjectTag::Player)
        .create();

    // スカイボックスオブジェクトを子要素に追加する
    gameObject->addChild(Act3D_SkyBox::create());

    return gameObject;
}
