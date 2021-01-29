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
	// 出現するオブジェクトの種類に対応する文字列の連想配列
	std::unordered_map<std::string, SpawnObjectType> spawnObjectTypeMap
	{
		{ "StreamingLine",			SpawnObjectType::StreamingLine },
		{ "BaseBackGround",			SpawnObjectType::BaseBackGround },
		{ "BaseBackGroundStopper",	SpawnObjectType::BaseBackGroundStopper },
		{ "TankEnemy",				SpawnObjectType::TankEnemy },
		{ "SpreadBulletEnemy",		SpawnObjectType::SpreadBulletEnemy }
	};

	// CSVデータを読み込み、文字列の２次元配列として取得する
	std::vector<std::vector<std::string>> csvDataArray = tktkFileIo::CsvFileReader::fileRead(csvFilePath, ',');

	// 敵出現データの一次保存リスト
	std::forward_list<std::unique_ptr<SpawnObjectData>> tempList;

	// 出現させるオブジェクト数のカウンタ
	size_t spawnObjectCount = 0U;

	// 読み込んだCSVデータを行ごとにループさせる
	for (const std::vector<std::string>& csvLineData : csvDataArray)
	{
		// 行データが不足していたら次の要素へ
		if (csvLineData.size() < 2U) continue;

		// 出現させるオブジェクトデータを作る
		std::unique_ptr<SpawnObjectData> spawnObjectData = std::make_unique<SpawnObjectData>();

		// “文字列->数値変換”を行う為の「文字列ストリーム」を作る
		std::istringstream ss;

		// 出現時間を取得
		ss = std::istringstream(csvLineData.at(0U));
		ss >> spawnObjectData->spawnTimeSec;

		// 座標、回転情報を含む出現情報だったら
		if (csvLineData.size() > 2U)
		{
			// ｘ座標を取得する
			ss = std::istringstream(csvLineData.at(2U));
			ss >> spawnObjectData->spawnPos.x;

			// ｙ座標を取得する
			ss = std::istringstream(csvLineData.at(3U));
			ss >> spawnObjectData->spawnPos.y;

			// 回転を取得する
			ss = std::istringstream(csvLineData.at(4U));
			ss >> spawnObjectData->spawnRotateDeg;
		}

		// オブジェクトの種類を取得するために、文字列から識別するための連想配列を使用する
		spawnObjectData->objectType = spawnObjectTypeMap.at(csvLineData.at(1U));

		// 一次保存リストに敵出現データを追加する
		tempList.push_front(std::move(spawnObjectData));

		// 出現させるオブジェクト数のカウンタをインクリメント
		spawnObjectCount++;
	}

	// 一次保存リストを出現時間順にソートする
	tempList.sort([](auto& a, auto& b) { return a->spawnTimeSec < b->spawnTimeSec; });

	// 敵出現データの配列のメモリを必要分確保する
	m_spawnObjectDataArray.reserve(spawnObjectCount);

	// 一次保存リストの要素をループする
	for (std::unique_ptr<SpawnObjectData>& spawnObjectData : tempList)
	{
		// 敵出現データの配列に敵出現データを移動する
		m_spawnObjectDataArray.push_back(std::move(spawnObjectData));
	}
}

void Sht2D_ObjectSpawnerScript::update()
{
	// 出現タイマーをカウントアップ
	m_curTime += tktk::DX12Game::deltaTime();

	// 「break」するまで無限ループ
	while (true)
	{
		// 全てのオブジェクトを出現させていたらループを終了する
		if (m_curSpawnObjectCount >= m_spawnObjectDataArray.size()) break;

		// 次に出現させるオブジェクトの情報を取得する
		const std::unique_ptr<SpawnObjectData>& nextSpawnObjectData = m_spawnObjectDataArray.at(m_curSpawnObjectCount);

		// 次に出現させる時間が過ぎていたら
		if (nextSpawnObjectData->spawnTimeSec < m_curTime)
		{
			// 出現させるオブジェクトの種類で分岐させる
			switch (nextSpawnObjectData->objectType)
			{
			// “流れる線”オブジェクトだったら
			case SpawnObjectType::StreamingLine:

				// 流れる線オブジェクトスポナーを生成する
				Sht2D_StreamingLineSpawner::create();
				break;

			// “基地の背景”オブジェクトだったら
			case SpawnObjectType::BaseBackGround:

				// 基地の背景オブジェクトスポナーを生成する
				Sht2D_BaseBackGroundSpawner::create();
				break;

			// “基地の背景生成停止”オブジェクトだったら
			case SpawnObjectType::BaseBackGroundStopper:

				// 基地の背景生成停止オブジェクトを生成する
				Sht2D_BaseBackGroundSpawnStopper::create();
				break;

			// “戦車エネミー”オブジェクトだったら
			case SpawnObjectType::TankEnemy:

				// 戦車エネミーオブジェクトを生成する
				Sht2D_TankEnemy::create(nextSpawnObjectData->spawnPos, nextSpawnObjectData->spawnRotateDeg);
				break;

			// “拡散弾エネミー”オブジェクトだったら
			case SpawnObjectType::SpreadBulletEnemy:

				// 拡散弾エネミーオブジェクトを生成する
				Sht2D_SpreadBulletEnemy::create(nextSpawnObjectData->spawnPos, nextSpawnObjectData->spawnRotateDeg);
				break;
			}

			// 出現数カウンタをインクリメントする
			m_curSpawnObjectCount++;
		}
		// 次に出現させる時間が来ていなかったらループを終了する
		else break;
	}
}