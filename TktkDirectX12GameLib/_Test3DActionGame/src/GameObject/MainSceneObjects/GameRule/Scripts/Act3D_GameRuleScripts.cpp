#include "Act3D_GameRuleScripts.h"

#include "../../../../Enums/Enums.h"

#include "../../EnemyObjects/FighterEnemy/Act3D_FighterEnemy.h"
#include "../../EnemyObjects/ShooterEnemy/Act3D_ShooterEnemy.h"
#include "../../EnemyObjects/BossEnemy/Act3D_BossEnemy.h"

#include "../../../MainSceneObjects/MainSceneChanger/Act3D_MainSceneChanger.h"

void Act3D_GameRuleScripts::start()
{
	m_playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);
}

void Act3D_GameRuleScripts::update()
{
	// �Q�[�����I�����Ă����珈�����I����
	if (!m_gamePlaying) return;

	// �v���C���[�����S���Ă�����
	if (m_playerObject.expired() || m_playerObject->containState(PlayerStateType::Dead))
	{
		// �V�[���J�ڃR���|�[�l���g�����
		Act3D_MainSceneChanger::create();

		// �Q�[���I�[�o�[�t���O�𗧂Ă�
		m_isGameOver = true;

		// �Q�[���v���C���t���O��܂�
		m_gamePlaying = false;

		return;
	}

	// �v���C���[�փ��b�Z�[�W�𑗐M����t���O�������Ă�����
	if (m_sendPlayerMessageNextFrame)
	{
		// �v���C���[�ɓG�̕��֌������b�Z�[�W�𑗐M����
		m_playerObject->sendMessage(EventMessageType::LookToEnemy);

		// ���b�Z�[�W���M�t���O��܂�
		m_sendPlayerMessageNextFrame = false;
	}

	// �G�̏o���������s��
	spawnEnemyCheck();
}

bool Act3D_GameRuleScripts::isGameOver() const
{
	return m_isGameOver;
}

void Act3D_GameRuleScripts::spawnEnemyCheck()
{
	// �G�I�u�W�F�N�g�̃��X�g���擾����
	auto enemyObjectList = tktk::DX12Game::findGameObjectsWithTag(GameObjectTag::Enemy);

	// �G�����݂��Ȃ�������
	if (enemyObjectList.empty())
	{
		// �S�Ă̓G���o�����Ă�����
		if (m_enemySpawnCounter >= static_cast<int>(SpawnData.size()))
		{
			// �V�[���J�ڃR���|�[�l���g�����
			Act3D_MainSceneChanger::create();

			// �Q�[���v���C���t���O��܂�
			m_gamePlaying = false;

			return;
		}

		// ��������G�l�~�[�̌����Ă������\���x�N�g�����v�Z����
		auto rotateDir = m_playerObject->getComponent<tktk::Transform3D>()->getWorldPosition() - tktkMath::Vector3_v::zero;

		// �o��������G�̎�ނŕ���
		switch (SpawnData.at(m_enemySpawnCounter))
		{
		// �ߋ����U���G�l�~�[�̏ꍇ
		case SpawnEnemyType::Fighter:

			// �ߋ����U���G�l�~�[�𐶐�����
			Act3D_FighterEnemy::create(tktkMath::Vector3_v::zero, { 0.0f, tktkMath::Vector2::signedAngle({ rotateDir.x, rotateDir.z }, tktkMath::Vector2_v::up), 0.0f });
			break;

		// �������U���G�l�~�[�̏ꍇ
		case SpawnEnemyType::Shooter:

			// �������U���G�l�~�[�𐶐�����
			Act3D_ShooterEnemy::create(tktkMath::Vector3_v::zero, { 0.0f, tktkMath::Vector2::signedAngle({ rotateDir.x, rotateDir.z }, tktkMath::Vector2_v::up), 0.0f });
			break;

		// �{�X�G�l�~�[�̏ꍇ
		case SpawnEnemyType::Boss:

			// �{�X�G�l�~�[�𐶐�����
			Act3D_BossEnemy::create(tktkMath::Vector3_v::zero, { 0.0f, tktkMath::Vector2::signedAngle({ rotateDir.x, rotateDir.z }, tktkMath::Vector2_v::up), 0.0f });
			break;
		}

		// �G�̏o�����J�E���^���C���N�������g����
		++m_enemySpawnCounter;

		// ���̃t���[���Ńv���C���[�Ƀ��b�Z�[�W�𑗐M����t���O�𗧂Ă�
		m_sendPlayerMessageNextFrame = true;
	}
}
