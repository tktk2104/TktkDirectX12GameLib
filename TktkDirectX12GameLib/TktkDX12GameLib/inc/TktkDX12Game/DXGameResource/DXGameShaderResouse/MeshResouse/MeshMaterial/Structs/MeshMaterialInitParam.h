#ifndef MESH_MATERIAL_INIT_PARAM_H_
#define MESH_MATERIAL_INIT_PARAM_H_

/* class member */
#include <TktkMath/Structs/Color.h>

namespace tktk
{
	// メッシュのマテリアルを作るとき必要な情報
	struct MeshMaterialInitParam
	{
		// 使うパイプラインステートのハンドル
		size_t								usePipeLineStateHandle;

		// 使うディスクリプタヒープのハンドル
		size_t								useDescriptorHeapHandle;

		// マテリアルの環境光
		tktkMath::Color						materialAmbient		{ 0.25f, 1.0f };

		// マテリアルの拡散反射光
		tktkMath::Color						materialDiffuse		{ 0.25f, 1.0f };

		// マテリアルの鏡面反射光
		tktkMath::Color						materialSpecular	{ 0.25f, 1.0f };

		// マテリアルの自己発光
		tktkMath::Color						materialEmissive	{ 0.25f, 1.0f };

		// マテリアルの輝度
		float								materialShiniess	{ 1.0f };
	};
}
#endif // !MESH_MATERIAL_INIT_PARAM_H_