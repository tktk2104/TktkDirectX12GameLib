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
	std::unordered_map<std::string, SpawnObjectType> spawnObjectTypeMap
	{
		{ "StreamingLine",			SpawnObjectType::StreamingLine },
		{ "BaseBackGround",			SpawnObjectType::BaseBackGround },
		{ "BaseBackGroundStopper",	SpawnObjectType::BaseBackGroundStopper },
		{ "TankEnemy",				SpawnObjectType::TankEnemy },
		{ "SpreadBulletEnemy",		SpawnObjectType::SpreadBulletEnemy }
	};

	auto csvDataArray = tktkFileIo::CsvFileReader::fileRead(csvFilePath, ',');

	std::forward_list<std::unique_ptr<SpawnObjectData>> tempList;

	size_t spawnObjectCount = 0U;

	for (const auto& csvLineData : csvDataArray)
	{
		if (csvLineData.size() < 2U) continue;

		SpawnObjectData spawnObjectData{};

		std::istringstream ss;

		ss = std::istringstream(csvLineData.at(0U));
		ss >> spawnObjectData.spawnTime;

		if (csvLineData.size() > 2U)
		{
			ss = std::istringstream(csvLineData.at(2U));
			ss >> spawnObjectData.spawnPos.x;

			ss = std::istringstream(csvLineData.at(3U));
			ss >> spawnObjectData.spawnPos.y;

			ss = std::istringstream(csvLineData.at(4U));
			ss >> spawnObjectData.spawnRotate;
		}

		spawnObjectData.objectType = spawnObjectTypeMap.at(csvLineData.at(1U));

		tempList.push_front(std::make_unique<SpawnObjectData>(spawnObjectData));

		spawnObjectCount++;
	}

	tempList.sort([](auto& a, auto& b) { return a->spawnTime < b->spawnTime; });

	m_spawnObjectDataArray.reserve(spawnObjectCount);

	for (auto& spawnObjectData : tempList)
	{
		m_spawnObjectDataArray.push_back(std::move(spawnObjectData));
	}
}

void Sht2D_ObjectSpawnerScript::update()
{
	m_curTime += tktk::DX12Game::deltaTime();

	while (true)
	{
		if (m_curSpawnObjectCount >= m_spawnObjectDataArray.size()) break;

		const auto& nextSpawnObjectData = m_spawnObjectDataArray.at(m_curSpawnObjectCount);

		if (nextSpawnObjectData->spawnTime < m_curTime)
		{
			switch (nextSpawnObjectData->objectType)
			{
			case SpawnObjectType::StreamingLine:

				Sht2D_StreamingLineSpawner::create();
				break;

			case SpawnObjectType::BaseBackGround:

				Sht2D_BaseBackGroundSpawner::create();
				break;

			case SpawnObjectType::BaseBackGroundStopper:

				Sht2D_BaseBackGroundSpawnStopper::create();
				break;

			case SpawnObjectType::TankEnemy:

				Sht2D_TankEnemy::create(nextSpawnObjectData->spawnPos, nextSpawnObjectData->spawnRotate);
				break;

			case SpawnObjectType::SpreadBulletEnemy:

				Sht2D_SpreadBulletEnemy::create(nextSpawnObjectData->spawnPos, nextSpawnObjectData->spawnRotate);
				break;
			}

			m_curSpawnObjectCount++;
		}
		else
		{
			break;
		}
	}
}