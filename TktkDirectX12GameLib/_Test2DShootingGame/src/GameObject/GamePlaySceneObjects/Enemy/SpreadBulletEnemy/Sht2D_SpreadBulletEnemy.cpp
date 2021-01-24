#include "Sht2D_SpreadBulletEnemy.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_DoubleSideMove.h"
#include "Scripts/Sht2D_SpreadBulletEnemyCombatStarter.h"
#include "Scripts/Sht2D_SpreadBulletEnemyDamager.h"
#include "Scripts/Sht2D_SpreadBulletEnemyBulletCreator.h"
#include "../_CommonEnemyScripts/CollisionReaction/Sht2D_EnemyCollisionReaction.h"
#include "../../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"
#include "../../../_CommonScripts/MoveForward/Sht2D_MoveForward.h"
#include "../../../_CommonScripts/AutoRotater/Sht2D_AutoRotater.h"
#include "../../../_CommonScripts/GameClearMessageSender/Sht2D_GameClearMessageSender.h"

namespace
{
    // 描画用オブジェクト
    inline tktk::GameObjectPtr createSpriteObject()
    {
        auto gameObject = tktk::DX12Game::createGameObject();

        // 二次元座標管理コンポーネント
        tktk::Transform2DMaker::makeStart(gameObject)
            .create();

        // スプライト描画コンポーネント
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::SpreadBulletEnemy)
            .create();

        // 自動回転コンポーネント
        gameObject->createComponent<Sht2D_AutoRotater>(720.0f);

        return gameObject;
    }

    // 入場ステートの準備をする
    inline void setupEntryState(tktk::GameObjectPtr gameObject)
    {
        //  生存ステートに追加する設定を行う
        gameObject->setTargetHierarchy({ SpreadBulletEnemyState::Alive, SpreadBulletEnemyState::Entry });
        {
            // 前方に移動するコンポーネント（毎秒移動速度, 毎秒加速速度）
            gameObject->createComponent<Sht2D_MoveForward>(150.0f, 4096.0f);
        
            gameObject->createComponent<Sht2D_SpreadBulletEnemyCombatStarter>();
        }
        // 特定の状態に追加する設定を解除する
        gameObject->setTargetHierarchy({ });
    }

    // 戦闘ステートの準備をする
    inline void setupCombatState(tktk::GameObjectPtr gameObject)
    {
        //  生存ステートに追加する設定を行う
        gameObject->setTargetHierarchy({ SpreadBulletEnemyState::Alive, SpreadBulletEnemyState::Combat });
        {
            gameObject->createComponent<Sht2D_SpreadBulletEnemyBulletCreator>();

            gameObject->createComponent<Sht2D_DoubleSideMove>(
                100.0f, 2048.0f,
                512.0f, tktk::DX12Game::getScreenSize().x - 512.0f
                );
        }
        // 特定の状態に追加する設定を解除する
        gameObject->setTargetHierarchy({ });
    }

    // 生存ステートの準備をする
    inline void setupAliveState(tktk::GameObjectPtr gameObject)
    {
        //  生存ステートに追加する設定を行う
        gameObject->setTargetHierarchy({ SpreadBulletEnemyState::Alive });
        {
            tktk::CircleColliderMaker::makeStart(gameObject)
                .radius(32.0f)
                .collisionGroupType(CollisionGroup::Enemy)
                .create();

            gameObject->createComponent<Sht2D_SpreadBulletEnemyDamager>();
        }
        // 特定の状態に追加する設定を解除する
        gameObject->setTargetHierarchy({ });

        // 入場ステートの準備をする
        setupEntryState(gameObject);

        // 戦闘ステートの準備をする
        setupCombatState(gameObject);
    }

    // 死亡ステートの準備をする
    inline void setupDeadState(tktk::GameObjectPtr gameObject)
    {
        //  生存ステートに追加する設定を行う
        gameObject->setTargetHierarchy({ SpreadBulletEnemyState::Dead });
        {
            // ゲームをクリアしたメッセージを送信するコンポーネント
            gameObject->createComponent<Sht2D_GameClearMessageSender>();

            // 前方に移動するコンポーネント（毎秒移動速度, 毎秒加速速度）
            gameObject->createComponent<Sht2D_MoveForward>(700.0f, 1124.0f);

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

tktk::GameObjectPtr Sht2D_SpreadBulletEnemy::create(const tktkMath::Vector2& position, float rotate)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // 敵であることを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::Enemy);

    // ボスであることを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::Boss);

    // 敵の攻撃範囲であることを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::EnemyAttackRange);

    // ステートマシンを使用する準備を行う
    tktk::StateMachineListInitParam stateInitParam{};

    // 大元のステートは「生存」と「死亡」のどちらか
    stateInitParam.initRootNode({ SpreadBulletEnemyState::Alive, SpreadBulletEnemyState::Dead });

    // 生存ステートは「入場」と「戦闘」のどちらか
    stateInitParam.addChildNode({ SpreadBulletEnemyState::Alive }, { SpreadBulletEnemyState::Entry, SpreadBulletEnemyState::Combat });

    // ステートマシンの初期化を行う
    gameObject->setupStateMachine(stateInitParam);

    // 最初は生存、入場ステート
    gameObject->statesEnable({ SpreadBulletEnemyState::Alive, SpreadBulletEnemyState::Entry });

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotationDeg(rotate)
        .create();

    // 二次元慣性移動コンポーネント
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(1024.0f)
        .create();

    gameObject->addChild(createSpriteObject());

    // 接触時のダメージ
    gameObject->createComponent<Sht2D_DamagePower>(0.0f, 10.0f);

    // 拡散弾エネミー耐久力のコンポーネント
    gameObject->createComponent<Sht2D_HealthPoint>(1000.0f);

    // エネミーの衝突判定リアクションコンポーネント
    gameObject->createComponent<Sht2D_EnemyCollisionReaction>();

    // 生存ステートの準備をする
    setupAliveState(gameObject);

    // 死亡ステートの準備をする
    setupDeadState(gameObject);

    return gameObject;
}
