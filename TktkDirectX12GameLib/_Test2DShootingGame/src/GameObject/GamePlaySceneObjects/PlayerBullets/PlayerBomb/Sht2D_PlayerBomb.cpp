#include "Sht2D_PlayerBomb.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_PlayerBombActiveTimer.h"
#include "Scripts/Sht2D_PlayerBombCollisionReaction.h"
#include "Scripts/Sht2D_PlayerBombExplode.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"
#include "../../../_CommonScripts/MoveForward/Sht2D_MoveForward.h"
#include "../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"

namespace
{
    // 待機ステートの準備をする（プレイヤーボムオブジェクト、ボム起動時間）
    inline void setupIdleState(tktk::GameObjectPtr gameObject, float activeTimeSec)
    {
        //  待機ステートに追加する設定を行う
        gameObject->setTargetHierarchy({ PlayerBombStateType::Idle });
        {
            // スプライト描画コンポーネント
            tktk::SpriteDrawerMaker::makeStart(gameObject)
                .spriteMaterialId(SpriteId::BompCore)
                .blendRate(tktkMath::Color_v::red)
                .create();

            // プレイヤーボムのアクティブタイマーコンポーネント（ボム起動時間）
            gameObject->createComponent<Sht2D_PlayerBombActiveTimer>(activeTimeSec);
        }
        // 特定の状態に追加する設定を解除する
        gameObject->setTargetHierarchy({ });
    }

    // アクティブステートの準備をする
    inline void setupActiveState(tktk::GameObjectPtr gameObject)
    {
        //  アクティブステートに追加する設定を行う
        gameObject->setTargetHierarchy({ PlayerBombStateType::Active });
        {
            // スプライト描画コンポーネント
            tktk::SpriteDrawerMaker::makeStart(gameObject)
                .spriteMaterialId(SpriteId::BompCore)
                .blendRate(tktkMath::Color_v::blue)
                .create();

            // 円の衝突判定コンポーネント
            tktk::CircleColliderMaker::makeStart(gameObject)
                .radius(16.0f)
                .collisionGroupType(CollisionGroup::PlayerBullet)
                .create();

#ifdef _DEBUG

            // 衝突判定の境界線を描画するコンポーネント
            tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
                .lineColor(tktkMath::Color_v::blue)
                .create();

#endif // _DEBUG

            // プレイヤーボムの衝突判定リアクションコンポーネント
            gameObject->createComponent<Sht2D_PlayerBombCollisionReaction>();
        }
        // 特定の状態に追加する設定を解除する
        gameObject->setTargetHierarchy({ });
    }
}

tktk::GameObjectPtr Sht2D_PlayerBomb::create(const tktkMath::Vector2& position, float rotate, float moveSpeedPerSec, float activeTimeSec)
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // プレイヤーの攻撃範囲であることを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::PlayerAttackRange);

    // ステートマシンを使用する準備を行う
    tktk::StateMachineListInitParam stateInitParam{};

    // 大元のステートは「待機」と「アクティブ」のどちらか
    stateInitParam.initRootNode({ PlayerBombStateType::Idle, PlayerBombStateType::Active });

    // ステートマシンの初期化を行う
    gameObject->setupStateMachine(stateInitParam);

    // 最初は待機ステート
    gameObject->statesEnable({ PlayerBombStateType::Idle });

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotationDeg(rotate)
        .initScaleRate(tktkMath::Vector2(0.5f, 0.5f))
        .create();

    // 二次元慣性移動コンポーネント
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(0.0f)
        .create();

    // スプライト描画コンポーネント
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::BompFrame)
        .create();

    // 接触時のダメージ（接触開始時ダメージ、毎秒の接触中ダメージ）
    gameObject->createComponent<Sht2D_DamagePower>(30.0f, 0.0f);

    // 前方に移動するコンポーネント（毎秒移動速度, 毎秒加速速度）
    gameObject->createComponent<Sht2D_MoveForward>(moveSpeedPerSec, std::numeric_limits<float>::max());

    // 画面外に出たら自身を殺すコンポーネント
    gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
        tktkMath::Vector2(-256.0f, -256.0f),
        tktk::DX12Game::getScreenSize() + tktkMath::Vector2(256.0f, 256.0f)
        );

    // 起爆用コンポーネント（接触開始時ダメージ、毎秒の接触中ダメージ）
    gameObject->createComponent<Sht2D_PlayerBombExplode>(200.0f, 500.0f);

    // 待機ステートの準備をする（プレイヤーボムオブジェクト、ボム起動時間）
    setupIdleState(gameObject, activeTimeSec);

    // アクティブステートの準備をする
    setupActiveState(gameObject);

    return gameObject;
}