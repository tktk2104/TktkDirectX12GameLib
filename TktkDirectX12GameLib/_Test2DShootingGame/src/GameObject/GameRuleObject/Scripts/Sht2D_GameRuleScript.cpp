#include "Sht2D_GameRuleScript.h"

#include "../../../Enums/Enums.h"
#include "../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"
#include "../../GamePlaySceneObjects/Ui/GameClearText/Sht2D_GameClearText.h"
#include "../../GamePlaySceneObjects/Ui/GameOverText/Sht2D_GameOverText.h"

void Sht2D_GameRuleScript::start()
{
	// �v���C���[�I�u�W�F�N�g���擾����
	m_playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);
}

void Sht2D_GameRuleScript::update()
{
	// �v���C���[�I�u�W�F�N�g���擾�ł��Ȃ���Ί֐����I����
	if (m_playerObject.expired()) return;

	// �v���C���[�I�u�W�F�N�g����ϋv�̓R���|�[�l���g���擾����
	tktk::ComponentPtr<Sht2D_HealthPoint> playerHp = m_playerObject->getComponent<Sht2D_HealthPoint>();

	// �v���C���[�̑ϋv�͂��O�ȉ���������
	if (playerHp->outOfHp())
	{
		// �Q�[���I�[�o�[�e�L�X�g�𐶐�����
		Sht2D_GameOverText::create();

		// �S�ẴI�u�W�F�N�g�X�|�i�[���폜����
		for (const auto& objectSpawner : tktk::DX12Game::findGameObjectsWithTag(GameObjectTag::ObjectSpawner))
		{
			objectSpawner->setActive(false);
		}

		// �v���C���[�I�u�W�F�N�g�|�C���^������������
		m_playerObject = tktk::GameObjectPtr();
	}
}

void Sht2D_GameRuleScript::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	// �v���C���[�I�u�W�F�N�g���擾�ł��Ȃ���Ί֐����I����
	if (m_playerObject.expired()) return;

	// �Q�[���N���A���b�Z�[�W���擾������
	if (type.isSame(EventMessageType::GameClear))
	{
		// �Q�[���N���A�e�L�X�g�𐶐�����
		Sht2D_GameClearText::create();

		// �v���C���[�I�u�W�F�N�g�|�C���^������������
		m_playerObject = tktk::GameObjectPtr();
	}
}
