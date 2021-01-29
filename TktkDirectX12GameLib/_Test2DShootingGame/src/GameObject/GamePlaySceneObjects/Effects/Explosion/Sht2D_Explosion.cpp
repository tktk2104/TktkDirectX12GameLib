#include "Sht2D_Explosion.h"

#include "../../../../Enums/Enums.h"

#include "Script/Sht2D_ExplosionScript.h"

tktk::GameObjectPtr Sht2D_Explosion::create(
    const tktkMath::Vector2& position,
    const tktkMath::Vector2& posRandomRange,
    float intervalTimeSec,
    int totalNum,
    float effectEndTimeSec
    )
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .create();

    // �����̃X�v���C�g�A�j���[�V�����𕡐���������R���|�[�l���g
    tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
        .generateLocalPosRandomRange(posRandomRange)
        .generateIntervalTimeSec(intervalTimeSec)
        .generateNumPerOnce(1)
        .totalGenerateNum(totalNum)
        .spriteMaterialId(SpriteId::Explosion)
        .lifeTimeSec(1.0f)
        .moveSpeedPerSec(0.0f)
        .useAnimation(true)
        .totalAnimFrameSize(15U)
        .animSpeedRate(1.4f)
        .isLoop(false)
        .create();

    // ��莞�Ԍ�Ɏ��g���E���R���|�[�l���g
    gameObject->createComponent<Sht2D_ExplosionScript>(effectEndTimeSec);

    return gameObject;
}
