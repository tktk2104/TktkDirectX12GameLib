#ifndef DX_GAME_RESOURCE_NUM_H_
#define DX_GAME_RESOURCE_NUM_H_

#include "Mesh/MeshResourceNum.h"

namespace tktk
{
	// ゲームで使用する表面的なリソースの数
	struct DXGameResourceNum
	{
		// シーン数
		unsigned int sceneNum				{};

		// サウンド数
		unsigned int soundNum				{};

		// スプライトマテリアル数
		unsigned int spriteMaterialNum		{};

		// ライン２Dマテリアル数
		unsigned int line2DMaterialNum		{};

		// メッシュ関連リソース数
		MeshResourceNum meshResourceNum		{};

		// ポストエフェクトマテリアル数
		unsigned int postEffectMaterialNum	{};

		// カメラ数
		unsigned int cameraNum				{};

		// ライト数
		unsigned int lightNum				{};
	};
}
#endif // !DX_GAME_RESOURCE_NUM_H_