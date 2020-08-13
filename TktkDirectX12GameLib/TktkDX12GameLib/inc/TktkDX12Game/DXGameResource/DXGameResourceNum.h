#ifndef DX_GAME_RESOURCE_NUM_H_
#define DX_GAME_RESOURCE_NUM_H_

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

		// 通常メッシュ数
		unsigned int basicMeshNum			{};

		// 通常メッシュマテリアル数
		unsigned int basicMeshMaterialNum	{};

		// スケルトンデータ数
		unsigned int skeletonNum			{};

		// モーションデータ数
		unsigned int motionNum				{};

		// ポストエフェクトマテリアル数
		unsigned int postEffectMaterialNum	{};

		// カメラ数
		unsigned int cameraNum				{};

		// ライト数
		unsigned int lightNum				{};
	};
}
#endif // !DX_GAME_RESOURCE_NUM_H_