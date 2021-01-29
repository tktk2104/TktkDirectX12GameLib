#include "Sht2D_PlayerBombCreator.h"

#include "../../../../Enums/Enums.h"
#include "../../PlayerBullets/PlayerBomb/Sht2D_PlayerBomb.h"
#include "../../PlayerBullets/PlayerBomb/Scripts/Sht2D_PlayerBombExplode.h"

void Sht2D_PlayerBombCreator::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_PlayerBombCreator not found Transform2D");
	}

	m_playerBulletCount = getComponent<Sht2D_PlayerBulletCount>();

	if (m_playerBulletCount.expired())
	{
		throw std::runtime_error("Sht2D_PlayerBombCreator not found Sht2D_PlayerBulletCount");
	}
}

void Sht2D_PlayerBombCreator::update()
{
	// ���ˊԊu�^�C�}�[�J�E���g���O���傫�����
	if (m_shotIntervalSecTimer > 0.0f)
	{
		// �J�E���g�_�E�����Ċ֐����I����
		m_shotIntervalSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	// �{�����˃{�^����������Ă�����
	if (tktk::DX12Game::isPush(CommandId::ShotBomb))
	{
		// �{���I�u�W�F�N�g�����݂��Ȃ�������
		if (m_targetBombObject.expired())
		{
			// �{�������
			createBomb();
		}
		// �{���I�u�W�F�N�g�����݂�����
		else
		{
			// �{�����N������
			explodeBomb();
		}
	}
}

void Sht2D_PlayerBombCreator::createBomb()
{
	// �{���̎c�e���O�������珈�����I����
	if (m_playerBulletCount->getCurBombCount() <= 0) return;

	// �{���𐶐����Ă��̃|�C���^�����g�̃����o�ɑ������
	m_targetBombObject = Sht2D_PlayerBomb::create(tktkMath::Vector2(0.0f, -64.0f) * m_transform->calculateWorldMatrix(), m_transform->getWorldRotationDeg(), BombSpeedPerSec, BombActiveTimeSec);

	// �{���̎c�e���P���炷
	m_playerBulletCount->changeBombCount(-1);
}

void Sht2D_PlayerBombCreator::explodeBomb()
{
	// ���e���A�N�e�B�u��ԂŖ�����΋N���ł��Ȃ�
	if (!m_targetBombObject->containState(PlayerBombStateType::Active)) return;

	// �N���I
	m_targetBombObject->getComponent<Sht2D_PlayerBombExplode>()->explode();

	// ���g�̃����o�̃{���I�u�W�F�N�g�|�C���^������������
	m_targetBombObject = tktk::GameObjectPtr();

	// ���ˊԊu�^�C�}�[�����Z�b�g����
	m_shotIntervalSecTimer = ShotIntervalTimeSec;
}
