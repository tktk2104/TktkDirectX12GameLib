#include "Sht2D_GameOverTextScript.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_GameOverTextScript::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_GameOverTextScript not found Transform2D");
	}
}

void Sht2D_GameOverTextScript::update()
{
	// �e�L�X�g�̈ړ����I����Ă�����
	if (m_textMoveEnd)
	{
		// ������͂�������n�߂���
		if (tktk::DX12Game::isTrigger(CommandId::Decision))
		{
			// �Q�[���v���C�֌W�̃V�[���𖳌��ɂ���
			tktk::DX12Game::disableScene(SceneId::GamePlay);
			tktk::DX12Game::disableScene(SceneId::Stage1);
			tktk::DX12Game::disableScene(SceneId::Stage2);
			tktk::DX12Game::disableScene(SceneId::Stage3);

			// ���U���g�V�[���֑J�ڂ���
			tktk::DX12Game::enableScene(SceneId::Result);
		}
		return;
	}

	// ���݂̎��g�̍��W���擾����
	const tktkMath::Vector2& curPos = m_transform->getLocalPosition();
	
	// ���݂̂����W����ʂ̒�����艺�ɂ�������
	if (curPos.y > tktk::DX12Game::getScreenSize().y / 2.0f)
	{
		// ���g�̍��W����ʂ̒��S�Ɉړ�����
		m_transform->setLocalPosition(tktkMath::Vector2(curPos.x, tktk::DX12Game::getScreenSize().y / 2.0f));

		// �ړ��I���t���O�𗧂Ă�
		m_textMoveEnd = true;
	}
	// ���݂̂����W����ʂ̒�������ɂ�������
	else
	{
		// ���g�̍��W���ړ�����B
		m_transform->addLocalPosition(tktkMath::Vector2(0.0f, MoveYSpeedPerSec * tktk::DX12Game::deltaTime()));
	}
}
