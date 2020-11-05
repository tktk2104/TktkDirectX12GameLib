#ifndef BASIC_MESH_MATERIAL_INIT_PARAM_H_
#define BASIC_MESH_MATERIAL_INIT_PARAM_H_

#include <TktkMath/Structs/Color.h>

namespace tktk
{
	// 通常メッシュのマテリアルを作るとき必要な情報
	struct BasicMeshMaterialInitParam
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
#endif // !BASIC_MESH_MATERIAL_INIT_PARAM_H_