#include "Sht2D_PlayerMissile.h"

#include "../../../../Enums/Enums.h"
#include "Scrits/Sht2D_PlayerMissileActiveTimer.h"
#include "Scrits/Sht2D_PlayerMissileCollisionReaction.h"
#include "Scrits/Sht2D_PlayerMissileExplode.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"
#include "../../../_CommonScripts/MoveForward/Sht2D_MoveForward.h"
#include "../../../_CommonScripts/RoteteToObject/Sht2D_RoteteToObject.h"
#include "../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"
#include "../../Effects/Flame/Sht2D_Flame.h"

namespace
{
    // 待機ステートの準備をする
    inline void setupIdleState(tktk::GameObjectPtr gameObject, float activeTimeSec, const tktk::GameObjectPtr& lockOnTarget)
    {
        //  待機ステートに追加する設定を行う
        gameObject->setTargetHierarchy({ PlayerMissileStateType::Idle });
        {
            gameObject->createComponent<Sht2D_PlayerMissileActiveTimer>(activeTimeSec);

            if (!lockOnTarget.expired())
            {
                gameObject->createComponent<Sht2D_RoteteToObject>(
                    360.0f,
                    lockOnTarget
                    );
            }
        }
        // 特定の状態に追加する設定を解除する
        gameObject->setTargetHierarchy({ });
    }

    // アクティブステートの準備をする
    inline void setupActiveState(tktk::GameObjectPtr gameObject, float moveSpeedPerSec, float accelerationPerSec, const tktk::GameObjectPtr& lockOnTarget)
    {
        //  アクティブステートに追加する設定を行う
        gameObject->setTargetHierarchy({ PlayerMissileStateType::Active });
        {
            // 前方に移動するコンポーネント（毎秒移動速度, 毎秒加速速度）
            gameObject->createComponent<Sht2D_MoveForward>(moveSpeedPerSec, accelerationPerSec);
        
            // 炎エフェクトオブジェクトを自身の子要素に
            gameObject->addChild(Sht2D_Flame::create({ 0.0f, 34.0f }, 180.0f));

            if (!lockOnTarget.expired())
            {
                gameObject->createComponent<Sht2D_RoteteToObject>(
                    90.0f,
                    lockOnTarget
                    );
            }
        }
        // 特定の状態に追加する設定を解除する
        gameObject->setTargetHierarchy({ });
    }
}

tktk::GameObjectPtr Sht2D_PlayerMissile::create(const tktkMath::Vector2& position, const tktkMath::Vector2& initVelocity, float rotate, float moveSpeedPerSec, float accelerationPerSec, float activeTimeSec, const tktk::GameObjectPtr& lockOnTarget)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // プレイヤーの攻撃範囲であることを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::PlayerAttackRange);

    // ステートマシンを使用する準備を行う
    tktk::StateMachineListInitParam stateInitParam{};

    // 大元のステートは「待機」と「アクティブ」のどちらか
    stateInitParam.initRootNode({ PlayerMissileStateType::Idle, PlayerMissileStateType::Active });

    // ステートマシンの初期化を行う
    gameObject->setupStateMachine(stateInitParam);

    // 最初は待機ステート
    gameObject->statesEnable({ PlayerMissileStateType::Idle });

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotationDeg(rotate)
        .create();

    // 二次元慣性移動コンポーネント
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(0.0f)
        .initVelocity(initVelocity)
        .create();

    // スプライト描画コンポーネント
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Missile)
        .create();

    // 長方形の衝突判定コンポーネント
    tktk::RectColliderMaker::makeStart(gameObject)
        .rectSize({ 32.0f, 64.0f })
        .collisionGroupType(CollisionGroup::PlayerBullet)
        .create();

#ifdef _DEBUG

    // 衝突判定の境界線を描画するコンポーネント
    tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::blue)
        .create();

#endif // _DEBUG

    // 接触時のダメージ
    gameObject->createComponent<Sht2D_DamagePower>(30.0f, 0.0f);

    // 画面外に出たら自身を殺すコンポーネント
    gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
        tktkMath::Vector2(-256.0f),
        tktk::DX12Game::getScreenSize() + tktkMath::Vector2(256.0f)
        );

    // 起爆用コンポーネント
    gameObject->createComponent<Sht2D_PlayerMissileExplode>(60.0f, 200.0f);

    // プレイヤーミサイルの衝突判定リアクションコンポーネント
    gameObject->createComponent<Sht2D_PlayerMissileCollisionReaction>();

    // 待機ステートの準備をする
    setupIdleState(gameObject, activeTimeSec, lockOnTarget);

    // アクティブステートの準備をする
    setupActiveState(gameObject, moveSpeedPerSec, accelerationPerSec, lockOnTarget);

    return gameObject;
}
