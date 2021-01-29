#include "Sht2D_ObjectSpawnerScript.h"

#include <sstream>
#include <unordered_map>
#include <TktkFileIo/CsvFileReader.h>

#include "../../BackGround/StreamingLine/Sht2D_StreamingLineSpawner.h"
#include "../../BackGround/Base/Sht2D_BaseBackGroundSpawner.h"
#include "../../BackGround/Base/Sht2D_BaseBackGroundSpawnStopper.h"

#include "../../Enemy/TankEnemy/Sht2D_TankEnemy.h"
#include "../../Enemy/SpreadBulletEnemy/Sht2D_SpreadBulletEnemy.h"

Sht2D_ObjectSpawnerScript::Sht2D_ObjectSpawnerScript(const std::string& csvFilePath)
{
	// �o������I�u�W�F�N�g�̎�ނɑΉ����镶����̘A�z�z��
	std::unordered_map<std::string, SpawnObjectType> spawnObjectTypeMap
	{
		{ "StreamingLine",			SpawnObjectType::StreamingLine },
		{ "BaseBackGround",			SpawnObjectType::BaseBackGround },
		{ "BaseBackGroundStopper",	SpawnObjectType::BaseBackGroundStopper },
		{ "TankEnemy",				SpawnObjectType::TankEnemy },
		{ "SpreadBulletEnemy",		SpawnObjectType::SpreadBulletEnemy }
	};

	// CSV�f�[�^��ǂݍ��݁A������̂Q�����z��Ƃ��Ď擾����
	std::vector<std::vector<std::string>> csvDataArray = tktkFileIo::CsvFileReader::fileRead(csvFilePath, ',');

	// �G�o���f�[�^�̈ꎟ�ۑ����X�g
	std::forward_list<std::unique_ptr<SpawnObjectData>> tempList;

	// �o��������I�u�W�F�N�g���̃J�E���^
	size_t spawnObjectCount = 0U;

	// �ǂݍ���CSV�f�[�^���s���ƂɃ��[�v������
	for (const std::vector<std::string>& csvLineData : csvDataArray)
	{
		// �s�f�[�^���s�����Ă����玟�̗v�f��
		if (csvLineData.size() < 2U) continue;

		// �o��������I�u�W�F�N�g�f�[�^�����
		std::unique_ptr<SpawnObjectData> spawnObjectData = std::make_unique<SpawnObjectData>();

		// �g������->���l�ϊ��h���s���ׂ́u������X�g���[���v�����
		std::istringstream ss;

		// �o�����Ԃ��擾
		ss = std::istringstream(csvLineData.at(0U));
		ss >> spawnObjectData->spawnTimeSec;

		// ���W�A��]�����܂ޏo����񂾂�����
		if (csvLineData.size() > 2U)
		{
			// �����W���擾����
			ss = std::istringstream(csvLineData.at(2U));
			ss >> spawnObjectData->spawnPos.x;

			// �����W���擾����
			ss = std::istringstream(csvLineData.at(3U));
			ss >> spawnObjectData->spawnPos.y;

			// ��]���擾����
			ss = std::istringstream(csvLineData.at(4U));
			ss >> spawnObjectData->spawnRotateDeg;
		}

		// �I�u�W�F�N�g�̎�ނ��擾���邽�߂ɁA�����񂩂环�ʂ��邽�߂̘A�z�z����g�p����
		spawnObjectData->objectType = spawnObjectTypeMap.at(csvLineData.at(1U));

		// �ꎟ�ۑ����X�g�ɓG�o���f�[�^��ǉ�����
		tempList.push_front(std::move(spawnObjectData));

		// �o��������I�u�W�F�N�g���̃J�E���^���C���N�������g
		spawnObjectCount++;
	}

	// �ꎟ�ۑ����X�g���o�����ԏ��Ƀ\�[�g����
	tempList.sort([](auto& a, auto& b) { return a->spawnTimeSec < b->spawnTimeSec; });

	// �G�o���f�[�^�̔z��̃�������K�v���m�ۂ���
	m_spawnObjectDataArray.reserve(spawnObjectCount);

	// �ꎟ�ۑ����X�g�̗v�f�����[�v����
	for (std::unique_ptr<SpawnObjectData>& spawnObjectData : tempList)
	{
		// �G�o���f�[�^�̔z��ɓG�o���f�[�^���ړ�����
		m_spawnObjectDataArray.push_back(std::move(spawnObjectData));
	}
}

void Sht2D_ObjectSpawnerScript::update()
{
	// �o���^�C�}�[���J�E���g�A�b�v
	m_curTime += tktk::DX12Game::deltaTime();

	// �ubreak�v����܂Ŗ������[�v
	while (true)
	{
		// �S�ẴI�u�W�F�N�g���o�������Ă����烋�[�v���I������
		if (m_curSpawnObjectCount >= m_spawnObjectDataArray.size()) break;

		// ���ɏo��������I�u�W�F�N�g�̏����擾����
		const std::unique_ptr<SpawnObjectData>& nextSpawnObjectData = m_spawnObjectDataArray.at(m_curSpawnObjectCount);

		// ���ɏo�������鎞�Ԃ��߂��Ă�����
		if (nextSpawnObjectData->spawnTimeSec < m_curTime)
		{
			// �o��������I�u�W�F�N�g�̎�ނŕ��򂳂���
			switch (nextSpawnObjectData->objectType)
			{
			// �g�������h�I�u�W�F�N�g��������
			case SpawnObjectType::StreamingLine:

				// �������I�u�W�F�N�g�X�|�i�[�𐶐�����
				Sht2D_StreamingLineSpawner::create();
				break;

			// �g��n�̔w�i�h�I�u�W�F�N�g��������
			case SpawnObjectType::BaseBackGround:

				// ��n�̔w�i�I�u�W�F�N�g�X�|�i�[�𐶐�����
				Sht2D_BaseBackGroundSpawner::create();
				break;

			// �g��n�̔w�i������~�h�I�u�W�F�N�g��������
			case SpawnObjectType::BaseBackGroundStopper:

				// ��n�̔w�i������~�I�u�W�F�N�g�𐶐�����
				Sht2D_BaseBackGroundSpawnStopper::create();
				break;

			// �g��ԃG�l�~�[�h�I�u�W�F�N�g��������
			case SpawnObjectType::TankEnemy:

				// ��ԃG�l�~�[�I�u�W�F�N�g�𐶐�����
				Sht2D_TankEnemy::create(nextSpawnObjectData->spawnPos, nextSpawnObjectData->spawnRotateDeg);
				break;

			// �g�g�U�e�G�l�~�[�h�I�u�W�F�N�g��������
			case SpawnObjectType::SpreadBulletEnemy:

				// �g�U�e�G�l�~�[�I�u�W�F�N�g�𐶐�����
				Sht2D_SpreadBulletEnemy::create(nextSpawnObjectData->spawnPos, nextSpawnObjectData->spawnRotateDeg);
				break;
			}

			// �o�����J�E���^���C���N�������g����
			m_curSpawnObjectCount++;
		}
		// ���ɏo�������鎞�Ԃ����Ă��Ȃ������烋�[�v���I������
		else break;
	}
}