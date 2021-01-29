#include "Sht2D_BaseBackGroundSpawnerScript.h"

#include "../../../../../Enums/Enums.h"
#include "../../_Scripts/Sht2D_BackGroundScript.h"
#include "../../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"

namespace
{
	tktk::GameObjectPtr createBackGround(const tktkMath::Vector2& position, const tktkMath::Vector2& velocityPerSec, SpriteId spriteId)
	{
		// �Q�[���I�u�W�F�N�g�����
		tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

		// �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
		gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

		// �񎟌����W�Ǘ��R���|�[�l���g
		tktk::Transform2DMaker::makeStart(gameObject)
			.initPosition(position)
			.create();

		// �X�v���C�g�`��R���|�[�l���g
		tktk::SpriteDrawerMaker::makeStart(gameObject)
			.spriteMaterialId(spriteId)
			.create();

		// �w�i�摜�̃X�N���[���R���|�[�l���g�i���b�̈ړ����x�j
		gameObject->createComponent<Sht2D_BackGroundScript>(velocityPerSec);

		// ��ʊO�ɏo���玩�g���E���R���|�[�l���g�i��ʔ͈͂̍�����W�A��ʔ͈͂̉E�����W�j
		gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
			tktkMath::Vector2(-512.0f, -512.0f),
			tktk::DX12Game::getScreenSize() + tktkMath::Vector2(512.0f, 512.0f)
			);

		return gameObject;
	}
}

void Sht2D_BaseBackGroundSpawnerScript::awake()
{
	// �����w�i�𐶐�����
	createBackGround(FirstSpawnPos + tktkMath::Vector2(0.0f, 512.0f), VelocityPerSec, SpriteId::BackGround_Base_1);
	createBackGround(FirstSpawnPos + tktkMath::Vector2(0.0f, 1024.0f), VelocityPerSec, SpriteId::BackGround_Base_1);

	// ��ԍŌ�ɐ��������w�i�I�u�W�F�N�g�̃|�C���^�������o�ŕێ�����
	m_beforeCreatedObject = createBackGround(FirstSpawnPos, VelocityPerSec, SpriteId::BackGround_Base_1);
}

void Sht2D_BaseBackGroundSpawnerScript::update()
{
	// �O�񐶐������w�i�I�u�W�F�N�g�|�C���^���󂾂����炱�̊֐����I����
	if (m_beforeCreatedObject.expired()) return;

	// �O�񐶐������w�i�̍��W�Ǘ��R���|�[�l���g���擾����
	tktk::ComponentPtr<tktk::Transform2D> beforeCreatedObjectTransform = m_beforeCreatedObject->getComponent<tktk::Transform2D>();

	// ��ʂ̏�ɔw�i�̖����̈悪�ł�������������
	if (beforeCreatedObjectTransform->getWorldPosition().y > 128.0f)
	{
		// �w�i�̐������~�߂�t���O�������Ă�����
		if (m_endSpawn)
		{
			// ��n�̖��[�w�i�摜�I�u�W�F�N�g���o��������
			createBackGround(beforeCreatedObjectTransform->getWorldPosition() - tktkMath::Vector2(0.0f, 512.0f) + VelocityPerSec * tktk::DX12Game::deltaTime(), VelocityPerSec, SpriteId::BackGround_Base_2);

			// �O�񐶐������w�i�I�u�W�F�N�g�|�C���^����ɂ���
			m_beforeCreatedObject = tktk::GameObjectPtr();

			// ���̊֐����I����
			return;
		}

		// �V���Ȕw�i�摜�I�u�W�F�N�g���o��������
		m_beforeCreatedObject = createBackGround(beforeCreatedObjectTransform->getWorldPosition() - tktkMath::Vector2(0.0f, 512.0f) + VelocityPerSec * tktk::DX12Game::deltaTime(), VelocityPerSec, SpriteId::BackGround_Base_1);
	}
}

void Sht2D_BaseBackGroundSpawnerScript::endSpawn()
{
	m_endSpawn = true;
}
