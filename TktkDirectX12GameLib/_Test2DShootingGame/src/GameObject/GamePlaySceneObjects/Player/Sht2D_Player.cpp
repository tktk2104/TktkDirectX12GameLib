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

  /*┌────────────────────────────────────────────────────────────────────────────────────────
    │下に実装されている関数はプレイヤーのステートパターンの設定関数です。
    │　ステートパターンの解説を見てから説明をしたいので、“行目”までスクロールして下さい
    └────────────────────────────────────────────────────────────────────────────────────────*/

namespace
{
    // 生存ステートの準備をする
    inline void setupAliveState(tktk::GameObjectPtr gameObject)
    {
      /*┌────────────────────────────────────────────────────────────────────────────────────────
        │特定のステートに属するコンポーネントや子要素を追加したい場合は、「gameObject->setTargetHierarchy(stateType)」を使って下さい。
        │　もう一度同じ関数を呼ぶまで追加するコンポーネントや子要素が指定したステートに属するようになります。
        └────────────────────────────────────────────────────────────────────────────────────────*/

        //  生存ステートに追加する設定を行う
        gameObject->setTargetHierarchy({ PlayerStateType::Alive });
        {
          /*┌────────────────────────────────────────────────────────────────────────────────────────
            │「RectColliderMaker」を使うことで「RectCollider」のコンポーネントを作る事ができます。
            │　「RectCollider」コンポーネントは長方形の衝突判定を行うコンポーネントです。
            │　衝突判定コンポーネントは他にも円の衝突判定を行う「CircleCollider」や、多角形ポリゴンの衝突判定を行う「Polygon2dCollider」があります。
            └────────────────────────────────────────────────────────────────────────────────────────*/

            // 長方形の衝突判定コンポーネント
            tktk::RectColliderMaker::makeStart(gameObject)
                .rectSize(tktkMath::Vector2(32.0f, 88.0f))
                .collisionGroupType(CollisionGroup::Player)
                .create();

            /*┌────────────────────────────────────────────────────────────────────────────────────────
              │「ColliderWireFrameDrawer2DMaker」を使うことで「ColliderWireFrameDrawer2D」のコンポーネントを作る事ができます。
              │　「ColliderWireFrameDrawer2D」コンポーネントは２次元の衝突判定を行うコンポーネントの判定の範囲を描画するコンポーネントです。
              │　※実際のゲームでは必要の無い描画処理なので条件コンパイルでデバックビルドのみ適応しています。
              └────────────────────────────────────────────────────────────────────────────────────────*/
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
            gameObject->addChild(Sht2D_Flame::create(tktkMath::Vector2(0.0f, 34.0f), 180.0f));
        }


      /*┌────────────────────────────────────────────────────────────────────────────────────────
        │特定のステートにコンポーネントや子要素を追加する状態を解除したい時は、「gameObject->setTargetHierarchy({})」を使って下さい。
        │　※引数に空の配列（正確には初期化子リスト）を渡すとステート無し扱いになります。
        └────────────────────────────────────────────────────────────────────────────────────────*/

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


          /*┌────────────────────────────────────────────────────────────────────────────────────────
            │「SpriteSpreadEffectCreatorMaker」を使うことで「SpriteSpreadEffectCreator」のコンポーネントを作る事ができます。
            │　「SpriteSpreadEffectCreator」コンポーネントは拡散するスプライトエフェクトを生成するコンポーネントです。
            │　とても大量のパラメーターが存在するので、「SpriteSpreadEffectCreatorMaker」に実装されている関数を参照して下さい。
            │　※兄弟コンポーネントとして「SpriteShrinkEffectCreator」が存在します。これは“収縮するスプライトエフェクト”を生成する物です。
            └────────────────────────────────────────────────────────────────────────────────────────*/
            
            // 被撃墜の煙のコンポーネント
            tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
                .spriteMaterialId(SpriteId::Spark)
                .generateLocalPosRandomRange(tktkMath::Vector2(48.0f, 48.0f))
                .generateIntervalTimeSec(0.1f)
                .generateNumPerOnce(1)
                .totalGenerateNum(-1)
                .spriteBlendRate(tktkMath::Color(0.2f, 0.6f))
                .setChild(false)
                .lifeTimeSec(1.0f)
                .moveSpeedPerSec(1024.0f)
                .spriteScale(0.6f)
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

tktk::GameObjectPtr Sht2D_Player::create(const tktkMath::Vector2& position)
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // プレイヤーを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::Player);

    // プレイヤーの攻撃範囲であることを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::PlayerAttackRange);


  /*┌────────────────────────────────────────────────────────────────────────────────────────
    │このフレームワークのゲームオブジェクトは“ステートマシン”という機能を持っています。
    │　この機能を使う為の初期設定を下の行で行っています。
    │　“ステートマシン”とは“ステートパターン”で処理を実装する時の助けとなる機能です。
    │　“ステートパターン”とは、複数の状態を定義し、その状態によって有効にするコンポーネントを変化させるものです。
    └────────────────────────────────────────────────────────────────────────────────────────*/

    // ステートマシンを使用する準備を行う
    tktk::StateMachineListInitParam stateInitParam{};


  /*┌────────────────────────────────────────────────────────────────────────────────────────
    │「tktk::StateMachineListInitParam」の構造体を使用して初期化を行います。
    │　この構造体には設定用関数が複数存在し、その１つに「stateMachineListInitParam.initRootNode(rootState)」があります。
    │　この関数では大元のステートの種類を設定します。
    │　「PlayerStateType」は自分で作る列挙型です。
    └────────────────────────────────────────────────────────────────────────────────────────*/

    // 大元のステートは「生存」と「死亡」のどちらか
    stateInitParam.initRootNode({ PlayerStateType::Alive, PlayerStateType::Dead });


  /*┌────────────────────────────────────────────────────────────────────────────────────────
    │「gameObject->setupStateMachine(stateMachineListInitParam)」を呼ぶことでステートマシンの初期化が完了します。
    └────────────────────────────────────────────────────────────────────────────────────────*/

    // ステートマシンの初期化を行う
    gameObject->setupStateMachine(stateInitParam);


  /*┌────────────────────────────────────────────────────────────────────────────────────────
    │特定のステートを有効にするには「gameObject->stateEnable(PlayerStateType::Alive)」を使って下さい。
    └────────────────────────────────────────────────────────────────────────────────────────*/

    // 最初は生存ステート
    gameObject->stateEnable(PlayerStateType::Alive);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .create();

  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│「InertialMovement2DMaker」を使うことで「InertialMovement2D」のコンポーネントを作る事ができます。
    │　「InertialMovement2D」コンポーネントは２次元慣性移動を行うコンポーネントです。
	└────────────────────────────────────────────────────────────────────────────────────────*/

    // 二次元慣性移動コンポーネント
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(1024.0f)
        .create();


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│「SpriteDrawerMaker」を使うことで「SpriteDrawer」のコンポーネントを作る事ができます。
    │　「SpriteDrawer」コンポーネントは読み込んだテクスチャを描画するコンポーネントです。
	└────────────────────────────────────────────────────────────────────────────────────────*/

    // スプライト描画コンポーネント
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Player)
        .create();

    // 接触時のダメージパワーコンポーネント（接触開始時ダメージ、毎秒の接触中ダメージ）
    gameObject->createComponent<Sht2D_DamagePower>(0.0f, 20.0f);

    // プレイヤー耐久力のコンポーネント（最大耐久力）
    gameObject->createComponent<Sht2D_HealthPoint>(100.0f);

    // プレイヤー弾数コンポーネント
    gameObject->createComponent<Sht2D_PlayerBulletCount>();


  /*┌────────────────────────────────────────────────────────────────────────────────────────
    │下の「Sht2D_PlayerCollisionReaction」をシングルクリック＆F12キーを入力してソースファイルに飛んで下さい。
    └────────────────────────────────────────────────────────────────────────────────────────*/

    // プレイヤーの衝突判定リアクションコンポーネント
    gameObject->createComponent<Sht2D_PlayerCollisionReaction>();


  /*┌────────────────────────────────────────────────────────────────────────────────────────
    │下の「setupAliveState(...)」をシングルクリック＆F12キーを入力して関数の実装に飛んで下さい。
    └────────────────────────────────────────────────────────────────────────────────────────*/

    // 生存ステートの準備をする
    setupAliveState(gameObject);


  /*┌────────────────────────────────────────────────────────────────────────────────────────
    │下の「setupDeadState(...)」をシングルクリック＆F12キーを入力して関数の実装に飛んで下さい。
    └────────────────────────────────────────────────────────────────────────────────────────*/

    // 死亡ステートの準備をする
    setupDeadState(gameObject);

    return gameObject;
}