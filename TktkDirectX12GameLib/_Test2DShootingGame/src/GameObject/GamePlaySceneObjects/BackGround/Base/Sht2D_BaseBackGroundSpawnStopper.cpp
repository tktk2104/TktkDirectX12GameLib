#include "Sht2D_BaseBackGroundSpawnStopper.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_BaseBackGroundSpawnStopperScript.h"

tktk::GameObjectPtr Sht2D_BaseBackGroundSpawnStopper::create()
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // ��n�̔w�i������~�R���|�[�l���g
    gameObject->createComponent<Sht2D_BaseBackGroundSpawnStopperScript>();

    return gameObject;
}
