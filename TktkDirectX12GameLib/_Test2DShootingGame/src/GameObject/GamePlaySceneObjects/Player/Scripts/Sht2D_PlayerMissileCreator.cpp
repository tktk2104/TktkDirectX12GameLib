#include "Sht2D_PlayerMissileCreator.h"

#include <limits>
#include "../../../../Enums/Enums.h"
#include "../../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"
#include "../../PlayerBullets/PlayerMissile/Sht2D_PlayerMissile.h"
#include "../../Ui/LockOnIcon/Sht2D_LockOnIcon.h"

void Sht2D_PlayerMissileCreator::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_PlayerMissileCreator not found Transform2D");
	}

	m_playerBulletCount = getComponent<Sht2D_PlayerBulletCount>();

	if (m_playerBulletCount.expired())
	{
		throw std::runtime_error("Sht2D_PlayerMissileCreator not found Sht2D_PlayerBulletCount");
	}
}

void Sht2D_PlayerMissileCreator::update()
{
	// ���ˊԊu�^�C�}�[���܂��O���傫�����
	if (m_shotIntervalSecTimer > 0.0f)
	{
		// �J�E���g�_�E�����ď������I����
		m_shotIntervalSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	// �~�T�C���̎c�e�����O�������珈�����I����
	if (m_playerBulletCount->getCurMissileCount() <= 0) return;

	// �~�T�C�����˃{�^����������n�߂���
	if (tktk::DX12Game::isTrigger(CommandId::ShotMissile))
	{
		// ���b�N�I���Ώۂ��擾����
		auto lockOnEnemyArray = findForwardLockOnEnemy(2U);

		// ���b�N�I���Ώۂ��P�̂ł����݂�����
		if (lockOnEnemyArray.size() >= 1U)
		{
			// ���b�N�I���A�C�R�����Q��������
			m_lockOnIconObjectArray = { Sht2D_LockOnIcon::create(), Sht2D_LockOnIcon::create() };

			// ��̖ڂ̓G�����b�N�I������
			lockOnEnemyArray.at(0U)->addChild(m_lockOnIconObjectArray.at(0U));

			// ���b�N�I���Ώۂ��Q�̑��݂�����
			if (lockOnEnemyArray.size() >= 2U)
			{
				// ��̖ڂ̓G�����b�N�I������
				lockOnEnemyArray.at(1U)->addChild(m_lockOnIconObjectArray.at(1U));
			}
			// ���b�N�I���Ώۂ��P�̂�������
			else
			{
				// ��̖ڂ̓G���d���b�N�I������
				lockOnEnemyArray.at(0U)->addChild(m_lockOnIconObjectArray.at(1U));
			}
		}

		// ���͎��ԃ^�C�}�[���J�E���g�A�b�v
		m_pushingSecTimer += tktk::DX12Game::deltaTime();

		return;
	}

	// �~�T�C�����˃{�^����������Ă�����
	if (tktk::DX12Game::isPush(CommandId::ShotMissile))
	{
		// ���͎��ԃ^�C�}�[���J�E���g�A�b�v
		m_pushingSecTimer += tktk::DX12Game::deltaTime();

		// ���b�N�I�����I����Ă��Ȃ����
		if (m_pushingSecTimer < MissileLockOnTimeSec)
		{
			// ���b�N�I���A�C�R�������k������
			for (tktk::GameObjectPtr& lockOnIconObject : m_lockOnIconObjectArray)
			{
				if (lockOnIconObject.expired()) continue;

				lockOnIconObject->getComponent<tktk::Transform2D>()->setLocalScaleRate({ 1.0f - (m_pushingSecTimer / MissileLockOnTimeSec) });
			}
		}
		else if (!m_lockOnReady)
		{
			for (tktk::GameObjectPtr& lockOnIconObject : m_lockOnIconObjectArray)
			{
				if (lockOnIconObject.expired()) continue;

				lockOnIconObject->getComponent<tktk::Transform2D>()->setLocalScaleRate(tktkMath::Vector2_v::one);
				lockOnIconObject->getComponent<tktk::SpriteDrawer>()->setSpriteMaterialId(SpriteId::LockOnReady);
			}

			m_lockOnReady = true;
		}
	}

	// �~�T�C�����˃{�^����������āA���͎��ԃ^�C�}�[���J�E���g�A�b�v���Ă�����
	else if(m_pushingSecTimer > 0.0f)
	{
		// �~�T�C���𔭎˂���
		shotMissile();

		// ���͎��ԃ^�C�}�[�����Z�b�g����
		m_pushingSecTimer = 0.0f;

		for (tktk::GameObjectPtr& lockOnIconObject : m_lockOnIconObjectArray)
		{
			if (!lockOnIconObject.expired()) lockOnIconObject->destroy();
		}
	}
}

std::vector<tktk::GameObjectPtr> Sht2D_PlayerMissileCreator::findForwardLockOnEnemy(size_t maxFindNum) const
{
	struct FindEnemyParam
	{
		tktk::GameObjectPtr object;
		float				dist;
		tktkMath::Vector2	pos;
	};

	// �Q�Ƃ����G�̐�
	size_t refEnemyCount = 0U;

	// �G�̏����v���C���[�ɋ߂����ɑ�����郊�X�g
	std::forward_list<FindEnemyParam> findEnemyParamList;

	// �S�Ă̓G�I�u�W�F�N�g�����[�v����
	for (const auto& enemy : tktk::DX12Game::findGameObjectsWithTag(GameObjectTag::Enemy))
	{
		// �����؂�|�C���^�������玟�̗v�f��
		if (enemy.expired()) continue;

		// ����ł���G�������玟�̗v�f��
		if (enemy->getComponent<Sht2D_HealthPoint>()->outOfHp()) continue;

		// �G�̍��W�Ǘ��R���|�[�l���g���擾����
		auto enemyTransform = enemy->getComponent<tktk::Transform2D>();

		// ���b�N�I���͈͊O�̓G�������牽�����Ȃ�
		if (tktkMath::Vector2::angle(m_transform->calculateWorldUp(), enemyTransform->getWorldPosition() - m_transform->getWorldPosition()) > MissileLockOnAngleRangeDeg) continue;

		// �G�Ƃ̋������v�Z����
		float selfEnemyPosDist = tktkMath::Vector2::distance(m_transform->getWorldPosition(), enemyTransform->getWorldPosition());

		// �������ʍő吔�ɒB���Ă��Ȃ���Ζⓚ���p�Œǉ�����
		if (refEnemyCount++ < maxFindNum)
		{
			findEnemyParamList.push_front({ enemy, selfEnemyPosDist, enemyTransform->getWorldPosition() });
		}
		else
		{
			// �G�Ƃ̋����̒Z�����X�V���Ă��邩�𔻒肷��
			for (auto& findEnemyParam : findEnemyParamList)
			{
				// �Z�����X�V���Ă����炻�̒l���X�V����
				if (selfEnemyPosDist < findEnemyParam.dist)
				{
					findEnemyParam = { enemy, selfEnemyPosDist, enemyTransform->getWorldPosition() };
					break;
				}
			}
		}

		// �������ʍő吔�ɒB�����u�ԂɁA�߂����ɂȂ�悤�ɗv�f���\�[�g����
		if (refEnemyCount == maxFindNum) findEnemyParamList.sort([](const FindEnemyParam& first, const FindEnemyParam& second) { return first.dist > second.dist; });
	}

	// �����W�����������ɂȂ�悤�ɗv�f���\�[�g����
	findEnemyParamList.sort([](const FindEnemyParam& first, const FindEnemyParam& second) { return first.pos.x < second.pos.x; });

	// �������ʂ�������z��
	std::vector<tktk::GameObjectPtr> result;

	// �������ʕ������z��̗v�f���m�ۂ���
	result.reserve((refEnemyCount < maxFindNum) ? refEnemyCount : maxFindNum);

	// �������ʂ�������
	for (const auto& findEnemyParam : findEnemyParamList)
	{
		result.push_back(findEnemyParam.object);
	}

	return result;
}

void Sht2D_PlayerMissileCreator::shotMissile()
{
	// ���b�N�I���Ώۂ̔z��
	std::array<tktk::GameObjectPtr, 2U> lockOntargetObjectArray;

	// ���b�N�I�����������Ă�����
	if (m_lockOnReady)
	{
		// ���b�N�I���A�C�R�����烍�b�N�I���Ώۂ��擾����
		for (size_t i = 0; i < 2U; i++)
		{
			if (m_lockOnIconObjectArray.at(i).expired()) continue;

			lockOntargetObjectArray.at(i) = m_lockOnIconObjectArray.at(i)->getParent();
		}
	}

	// �~�T�C�����P�����˂���
	Sht2D_PlayerMissile::create(tktkMath::Vector2(-32.0f, 0.0f) * m_transform->calculateWorldMatrix(), -InitVelocity, m_transform->getWorldRotationDeg(), MissileSpeedPerSec, MissileAccelerationPerSec, MissileActiveTimeSec, lockOntargetObjectArray.at(0U));

	// �~�T�C���c�e�����P���炷
	m_playerBulletCount->changeMissileCount(-1);

	// �~�T�C���c�e�����܂��c���Ă�����
	if (m_playerBulletCount->getCurMissileCount() > 0)
	{
		// �~�T�C���������P�����˂���
		Sht2D_PlayerMissile::create(tktkMath::Vector2(32.0f, 0.0f) * m_transform->calculateWorldMatrix(), InitVelocity, m_transform->getWorldRotationDeg(), MissileSpeedPerSec, MissileAccelerationPerSec, MissileActiveTimeSec, lockOntargetObjectArray.at(1U));

		// �~�T�C���c�e�����P���炷
		m_playerBulletCount->changeMissileCount(-1);
	}

	// ���b�N�I�������t���O��؂�
	m_lockOnReady = false;

	// ���ˊԊu�^�C�}�[���Z�b�g����
	m_shotIntervalSecTimer = ShotIntervalTimeSec;
}
