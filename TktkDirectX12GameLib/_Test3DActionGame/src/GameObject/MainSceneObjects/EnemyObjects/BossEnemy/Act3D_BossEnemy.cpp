#include "Act3D_BossEnemy.h"

#include "../../../../Enums/Enums.h"
#include "../../../_CommonScripts/GravityMove/Act3D_GravityMove.h"

#include "../_CommonEnemyScripts/Act3D_RotateToPlayer.h"
#include "../_CommonEnemyScripts/Act3D_RotateToPlayerInTime.h"
#include "../_CommonEnemyScripts/Act3D_MoveForward.h"
#include "../_CommonEnemyScripts/Act3D_EnemyAttackRangeGenerator.h"
#include "../_CommonEnemyScripts/Act3D_EnemyJampAttackMoving.h"
#include "../_CommonEnemyScripts/Act3D_EnemyCollisionReaction.h"
#include "../../../_CommonScripts/SelfDeadTimer/Act3D_SelfDeadTimer.h"

#include "Scripts/Act3D_BossEnemyParam.h"
#include "Scripts/Act3D_BossEnemyDamager.h"
#include "Scripts/Act3D_BossEnemyStartChase.h"
#include "Scripts/Act3D_BossEnemyStartAttack.h"
#include "Scripts/Act3D_BossEnemyStartDown.h"
#include "Scripts/Act3D_BossEnemyStartStandUp.h"
#include "Scripts/Act3D_BossEnemyEndAttack.h"
#include "Scripts/Act3D_BossEnemyEndDown.h"
#include "Scripts/Act3D_BossEnemyEndDamage.h"

// 待機状態の設定を行う
inline void setBossEnemyIdleState(tktk::GameObjectPtr gameObject)
{
    // 待機状態に追加する設定を行う
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Idle });
    {
        // プレイヤーとの位置関係によって移動状態に遷移するコンポーネント
        gameObject->createComponent<Act3D_BossEnemyStartChase>();

        // エネミーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_BossEnemyDamager>();

        // 待機モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyIlde).lerpTimeSec(0.1f).isLoop(true).create();
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// 移動状態の設定を行う
inline void setBossEnemyMoveState(tktk::GameObjectPtr gameObject)
{
    // 移動状態に追加する設定を行う
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Move });
    {
        // プレイヤーの方へ向くコンポーネント
        gameObject->createComponent<Act3D_RotateToPlayer>(180.0f);

        // 前方に進むコンポーネント
        gameObject->createComponent<Act3D_MoveForward>(3.0f);

        // プレイヤーとの位置関係によって攻撃状態に遷移させる
        gameObject->createComponent<Act3D_BossEnemyStartAttack>();

        // エネミーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_BossEnemyDamager>();

        // 移動モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyRun).lerpTimeSec(0.1f).isLoop(true).motionSpeedRate(0.7f).create();
    
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
inline void setBossEnemyAttackState(tktk::GameObjectPtr gameObject)
{
    // 通常攻撃状態に追加する設定を行う
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Attack, BossEnemyStateType::NormalAttack });
    {
        // 1.5秒間プレイヤーの方へ向くコンポーネント
        gameObject->createComponent<Act3D_RotateToPlayerInTime>(35.0f, 1.5f);

        // 3.3秒後に通常攻撃から移動状態に移行する処理を設定する
        gameObject->createComponent<Act3D_BossEnemyEndAttack>(3.3f, BossEnemyStateType::NormalAttack);

        // 1.5秒〜3.0秒の間通常攻撃の攻撃範囲を出現させるコンポーネント
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(1.5f, 3.0f, tktkMath::Vector3(0.0f, 2.0f, 2.5f), tktkMath::Vector3(3.0f, 3.0f, 4.0f));

        // エネミーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_BossEnemyDamager>();

        // 通常攻撃モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyNormalAttack).lerpTimeSec(0.1f).motionSpeedRate(0.8f).isLoop(false).create();
   
        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::BossEnemyNormalAttack)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::LightBlow)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.1f)
            .playCount(1)
            .create();
    }

    // ジャンプ攻撃状態に追加する設定を行う
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Attack, BossEnemyStateType::JumpAttack });
    {
        // 1.8秒間ジャンプ攻撃による移動を行うコンポーネント
        gameObject->createComponent<Act3D_EnemyJampAttackMoving>(5.0f, 0.5f, 8.0f, 1.8f);

        // ３秒後にジャンプ攻撃から移動状態に移行する処理を設定する
        gameObject->createComponent<Act3D_BossEnemyEndAttack>(3.0f, BossEnemyStateType::JumpAttack);

        // 1.4秒〜2.4秒の間ジャンプ攻撃の攻撃範囲を出現させるコンポーネント
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(1.4f, 2.4f, tktkMath::Vector3(0.0f, 1.0f, 0.0f), tktkMath::Vector3(5.0f, 1.0f, 5.0f));

        // ジャンプ攻撃モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyJumpAttack).lerpTimeSec(0.1f).isLoop(false).create();
    
        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::BossEnemyJumpAttack)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::HeavyBlow)
            .startToPlay(false)
            .firstPlayStartTimeSec(1.0f)
            .playCount(1)
            .create();

        // 収縮するビルボードパーティクルコンポーネント
        tktk::BillboardShrinkEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate(tktkMath::Color_v::red)
            .shrinkTargetPos({ 0.0f, 2.0f, 0.0f })
            .totalGenerateNum(30)
            .setChild(true)
            .changeAvtiveToReset(true)
            .create();

        // 拡散するビルボードパーティクルコンポーネント
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // グレー
            .generateLocalPos({ 0.0f, 0.5f, 0.0f })
            .generateLocalPosRandomRange({ 2.0f, 2.0f, 2.0f })
            .billboardScale({ 0.3f, 0.3f })
            .moveSpeedPerSec(2.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(20)
            .totalGenerateNum(60)
            .firstGenerateTimeSec(1.6f)
            .generateIntervalTimeSec(0.01f)
            .changeAvtiveToReset(true)
            .create();

        // 拡散するビルボードパーティクルコンポーネント
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // グレー
            .generateLocalPos({ 0.0f, 0.0f, 0.0f })
            .generateLocalPosRandomRange({ 2.0f, 2.0f, 2.0f })
            .moveSpeedPerSec(6.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(20)
            .totalGenerateNum(120)
            .firstGenerateTimeSec(1.6f)
            .generateIntervalTimeSec(0.02f)
            .changeAvtiveToReset(true)
            .create();
    }

    // ローリング攻撃状態に追加する設定を行う
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Attack, BossEnemyStateType::RollAttack });
    {
        // 1.8秒間ローリング攻撃による移動を行うコンポーネント
        gameObject->createComponent<Act3D_EnemyJampAttackMoving>(0.0f, 1.0f, 3.0f, 1.8f);

        // 1.5秒後にローリング攻撃から移動状態に移行する処理を設定する
        gameObject->createComponent<Act3D_BossEnemyEndAttack>(1.5f, BossEnemyStateType::RollAttack);

        // 0.0秒〜1.5秒の間ローリング攻撃の攻撃範囲を出現させるコンポーネント
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(0.0f, 1.5f, tktkMath::Vector3(0.0f, 1.0f, 2.0f), tktkMath::Vector3(4.0f, 1.0f, 4.0f));

        // ローリング攻撃モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyRoolAttack).lerpTimeSec(0.1f).isLoop(false).create();
    
        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::BossEnemyRollAttack)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::HeavyBlow)
            .startToPlay(false)
            .firstPlayStartTimeSec(1.0f)
            .playCount(1)
            .create();

        // 拡散するビルボードパーティクルコンポーネント
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // グレー
            .generateLocalPos({ 0.0f, 0.0f, 0.0f })
            .billboardScale({ 0.3f, 0.3f })
            .generateLocalPosRandomRange({ 2.0f, 2.0f, 2.0f })
            .moveSpeedPerSec(6.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(20)
            .generateIntervalTimeSec(0.1f)
            .changeAvtiveToReset(true)
            .create();
    }

    // 失敗ローリング状態に追加する設定を行う
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Attack, BossEnemyStateType::MissRool });
    {
        // ジャンプ攻撃による移動のコンポーネント
        gameObject->createComponent<Act3D_EnemyJampAttackMoving>(0.0f, 1.0f, 3.0f, 1.2f);

        // 失敗ローリング状態からダウン状態に移行する処理を設定する
        gameObject->createComponent<Act3D_BossEnemyStartDown>();

         // ジャンプ攻撃の攻撃範囲を出現させるコンポーネント
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(0.0f, 1.0f, tktkMath::Vector3(0.0f, 1.0f, 2.0f), tktkMath::Vector3(4.0f, 1.0f, 4.0f));

        // 失敗ローリングモーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyDown).lerpTimeSec(0.1f).isLoop(false).create();
    
        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::BossEnemyRollAttack)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
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
inline void setBossEnemyNormalState(tktk::GameObjectPtr gameObject)
{
    // 待機状態の設定を行う
    setBossEnemyIdleState(gameObject);

    // 移動状態の設定を行う
    setBossEnemyMoveState(gameObject);

    // 攻撃状態の設定を行う
    setBossEnemyAttackState(gameObject);
}

// 移動不能状態の設定を行う
inline void setBossEnemyCantMoveState(tktk::GameObjectPtr gameObject)
{
    // 移動不能状態に追加する設定を行う
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Down, BossEnemyStateType::CantMove });
    {
        // 行動不能状態から起き上がり状態に移行する処理を設定する
        gameObject->createComponent<Act3D_BossEnemyStartStandUp>();

        // エネミーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_BossEnemyDamager>();
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// 起き上がり状態の設定を行う
inline void setBossEnemyStandUpState(tktk::GameObjectPtr gameObject)
{
    // 起き上がり状態に追加する設定を行う
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Down, BossEnemyStateType::StandUp });
    {
        // ダウン状態を終える処理を設定する
        gameObject->createComponent<Act3D_BossEnemyEndDown>();

        // エネミーのダメージ処理コンポーネント
        gameObject->createComponent<Act3D_BossEnemyDamager>();

        // 起き上がりモーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyStandUp).lerpTimeSec(0.1f).motionSpeedRate(0.8f).isLoop(false).create();
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// ダウン状態の設定を行う
inline void setBossEnemyDownState(tktk::GameObjectPtr gameObject)
{
    // 移動不能状態の設定を行う
    setBossEnemyCantMoveState(gameObject);

    // 起き上がり状態の設定を行う
    setBossEnemyStandUpState(gameObject);
}

// 生存状態の設定を行う
inline void setBossEnemyAliveState(tktk::GameObjectPtr gameObject)
{
    // 生存状態に追加する設定を行う
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive });
    {
        // ３次元慣性移動コンポーネント
        tktk::InertialMovement3DMaker::makeStart(gameObject)
            .decelerationPerSec(1.0f)
            .craete();

        // OBB衝突判定コンポーネント
        tktk::BoxColliderMaker::makeStart(gameObject)
            .boxSize({ 3.0f, 6.0f, 3.0f })
            .localPosition({ 0.0f, 3.3f, 0.0f })
            .collisionGroupType(CollisionGroup::Enemy)
            .isExtrude(true)
            .extrudedRate(0.1f)
            .create();

        // エネミーの衝突判定のリアクション
        gameObject->createComponent<Act3D_EnemyCollisionReaction>();

        // 重力による移動コンポーネント
        gameObject->createComponent<Act3D_GravityMove>();
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});

    // 通常状態の設定を行う
    setBossEnemyNormalState(gameObject);

    // ダウン状態の設定を行う
    setBossEnemyDownState(gameObject);
}

// 死亡状態の設定を行う
inline void setBossEnemyDeadState(tktk::GameObjectPtr gameObject)
{
    // 死亡状態に追加する設定を行う
    gameObject->setTargetHierarchy({ BossEnemyStateType::Dead });
    {
        // 死亡モーションを行うコンポーネント
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyDead).lerpTimeSec(0.1f).isLoop(false).create();
    
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

        // 拡散するビルボードパーティクルコンポーネント
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // グレー
            .generateLocalPos({ 0.0f, 0.5f, 3.0f })
            .generateLocalPosRandomRange({ 2.0f, 2.0f, 2.0f })
            .billboardScale({ 0.3f, 0.3f })
            .moveSpeedPerSec(1.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(30)
            .totalGenerateNum(90)
            .firstGenerateTimeSec(2.4f)
            .generateIntervalTimeSec(0.01f)
            .changeAvtiveToReset(true)
            .create();

        // 拡散するビルボードパーティクルコンポーネント
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // グレー
            .generateLocalPos({ 0.0f, 0.0f, 3.0f })
            .generateLocalPosRandomRange({ 2.0f, 2.0f, 2.0f })
            .moveSpeedPerSec(3.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(30)
            .totalGenerateNum(180)
            .firstGenerateTimeSec(2.4f)
            .generateIntervalTimeSec(0.02f)
            .changeAvtiveToReset(true)
            .create();

        // サウンド再生タイマー
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::FighterEnemyDead)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // 一定時間後に自身を消すコンポーネント
        gameObject->createComponent<Act3D_SelfDeadTimer>(9.0f);
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

// ダメージ状態の設定を行う
inline void setBossEnemyDamageState(tktk::GameObjectPtr gameObject)
{
    // ダメージ状態に追加する設定を行う
    gameObject->setTargetHierarchy({ BossEnemyStateType::Damage });
    {
        // ダメージ状態を終了するコンポーネント
        gameObject->createComponent<Act3D_BossEnemyEndDamage>();

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
    }
    // 特定の状態に追加する設定を解除する
    gameObject->setTargetHierarchy({});
}

tktk::GameObjectPtr Act3D_BossEnemy::create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation)
{
    // ゲームオブジェクトを作成
    auto gameObject = tktk::DX12Game::createGameObject();

    // メインシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::MainSceneObject);

    // エネミータグとボスタグを追加
    gameObject->addGameObjectTag(GameObjectTag::Enemy);
    gameObject->addGameObjectTag(GameObjectTag::Boss);

    // ステートマシンを使用する準備を行う
    tktk::StateMachineListInitParam initParam{};

    // 大元のステートは「生存」か「死亡」「ダメージ」のいずれか（ダメージステートのみイレギュラー）
    initParam.initRootNode({ BossEnemyStateType::Alive, BossEnemyStateType::Dead, BossEnemyStateType::Damage });

    // 「生存ステート」は「通常」と「ダウン」の２つのステートから成り立っている
    initParam.addChildNode({ BossEnemyStateType::Alive }, { BossEnemyStateType::Normal, BossEnemyStateType::Down });

    // 「生存・通常ステート」には「待機」「移動」「攻撃」の３つのステートから成り立っている
    initParam.addChildNode({ BossEnemyStateType::Alive, BossEnemyStateType::Normal },
        { BossEnemyStateType::Idle, BossEnemyStateType::Move, BossEnemyStateType::Attack });

    // 「生存・通常・攻撃ステート」には「通常攻撃」「ジャンプ攻撃」「ローリング攻撃」「失敗ローリング」の４つのステートから成り立っている
    initParam.addChildNode({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Attack },
        { BossEnemyStateType::NormalAttack, BossEnemyStateType::JumpAttack, BossEnemyStateType::RollAttack, BossEnemyStateType::MissRool });

    // 「生存・ダウンステート」は「移動不能」と「起き上がり」の２つのステートから成り立っている
    initParam.addChildNode({ BossEnemyStateType::Alive, BossEnemyStateType::Down },
        { BossEnemyStateType::CantMove, BossEnemyStateType::StandUp });

    // ステートマシンの初期化
    gameObject->setupStateMachine(initParam);

    // 最初は「生存・通常・待機ステート」
    gameObject->statesEnable({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Idle });

    // 生存状態の設定を行う
    setBossEnemyAliveState(gameObject);

    // 死亡状態の設定を行う
    setBossEnemyDeadState(gameObject);

    // ダメージ状態の設定を行う
    setBossEnemyDamageState(gameObject);

    // ３次元座標コンポーネント
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotation(rotation)
        .create();

    // メッシュ描画コンポーネント
    tktk::MeshDrawerMaker::makeStart(gameObject)
        .meshId(MeshId::BossEnemy)
        .skeletonId(SkeletonId::BossEnemy)
        .baseScale(0.3f)
        .baseRotation(tktkMath::Quaternion::createFromEulerAngle({ 0.0f, 180.0f, 0.0f }))
        .create();

    // メッシュのアニメーションコンポーネント
    tktk::MeshAnimatorMaker::makeStart(gameObject)
        .initMotionId(MotionId::BossEnemyIlde)
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
    gameObject->createComponent<Act3D_BossEnemyParam>();

    return gameObject;
}
