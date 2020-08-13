#ifndef BASIC_MESH_LOAD_PMD_ARGS_H_
#define BASIC_MESH_LOAD_PMD_ARGS_H_

#include <string>

namespace tktk
{
	// pmdファイルを読み込むときに必要な情報
	struct BasicMeshLoadPmdArgs
	{
		// 作成する通常メッシュマテリアルのディスクリプタヒープの開始ID（複数マテリアルがある場合、この値を基準とした連番IDとなる）
		unsigned int createDescriptorHeapIdStartNum;

		// 作成する頂点バッファのID
		unsigned int createVertexBufferId;

		// 作成するインデックスバッファのID
		unsigned int createIndexBufferId;
		
		// 作成する通常メッシュ情報のID
		unsigned int createBasicMeshId;

		// 作成するスケルトン情報のID
		unsigned int createSkeletonId;

		// 作成する通常メッシュマテリアルの開始ID（複数マテリアルがある場合、この値を基準とした連番IDとなる）
		unsigned int createBasicMeshMaterialIdStartNum;

		// 作成するテクスチャの開始ID（複数テクスチャがある場合、この値を基準とした連番IDとなる）
		unsigned int createTextureIdStartNum;

		// 読み込むファイルパス
		std::string filePath;
	};
}
#endif // !BASIC_MESH_LOAD_PMD_ARGS_H_
