#include "Sht2D_StreamingLineSpawnerScript.h"

#include <TktkMath/Random.h>
#include "../../../../../Enums/Enums.h"
#include "../../_Scripts/Sht2D_BackGroundScript.h"
#include "../../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"

namespace
{
	// �������𐶐�����֐�
	tktk::GameObjectPtr createStreamingLine(const tktkMath::Vector2& position, const tktkMath::Vector2& velocityPerSec)
	{
		// �Q�[���I�u�W�F�N�g�����
		tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

		// �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
		gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

		// �񎟌����W�Ǘ��R���|�[�l���g
		tktk::Transform2DMaker::makeStart(gameObject)
			.initPosition(position)
			.initScaleRate(tktkMath::Vector2(0.1f, 0.4f))
			.create();

		// �X�v���C�g�`��R���|�[�l���g
		tktk::SpriteDrawerMaker::makeStart(gameObject)
			.spriteMaterialId(SpriteId::StreamingLine)
			.blendRate(tktkMath::Color(1.0f, 0.2f))
			.create();

		// �w�i�摜�̃X�N���[���R���|�[�l���g�i���b�̈ړ����x�j
		gameObject->createComponent<Sht2D_BackGroundScript>(velocityPerSec);

		// ��ʊO�ɏo���玩�g���E���R���|�[�l���g�i��ʔ͈͂̍�����W�A��ʔ͈͂̉E�����W�j
		gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
			tktkMath::Vector2(-128.0f, -128.0f),
			tktk::DX12Game::getScreenSize() + tktkMath::Vector2(128.0f, 128.0f)
			);

		return gameObject;
	}
}

void Sht2D_StreamingLineSpawnerScript::update()
{
	// �P�t���[���ŏo�����闬�����̐��������[�v����
	for (size_t i = 0; i < SpawnStreamingLineCountPerFrame; i++)
	{
		// �������𐶐�����
		createStreamingLine(tktkMath::Vector2(tktkMath::Random::getRandF(0.0f, tktk::DX12Game::getScreenSize().x), 0.0f), VelocityPerSec);
	}
}
