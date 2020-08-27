#ifndef DX_GAME_RESOURCE_NUM_H_
#define DX_GAME_RESOURCE_NUM_H_

#include "Mesh/MeshResourceNum.h"

namespace tktk
{
	// ゲームで使用する表面的なリソースを管理するコンテナを作るための変数
	struct DXGameResourceNum
	{
		// シーンを管理するコンテナを作るための変数
		tktkContainer::ResourceContainerInitParam sceneNum				{};

		// サウンドを管理するコンテナを作るための変数
		tktkContainer::ResourceContainerInitParam soundNum				{};

		// スプライトマテリアルを管理するコンテナを作るための変数
		tktkContainer::ResourceContainerInitParam spriteMaterialNum		{};

		// ライン２Dマテリアルを管理するコンテナを作るための変数
		tktkContainer::ResourceContainerInitParam line2DMaterialNum		{};

		// メッシュ関連リソースを管理するコンテナを作るための変数
		MeshResourceNum meshResourceNum									{};

		// ポストエフェクトマテリアルを管理するコンテナを作るための変数
		tktkContainer::ResourceContainerInitParam postEffectMaterialNum	{};

		// カメラを管理するコンテナを作るための変数
		tktkContainer::ResourceContainerInitParam cameraNum				{};

		// ライトを管理するコンテナを作るための変数
		tktkContainer::ResourceContainerInitParam lightNum				{};
	};
}
#endif // !DX_GAME_RESOURCE_NUM_H_