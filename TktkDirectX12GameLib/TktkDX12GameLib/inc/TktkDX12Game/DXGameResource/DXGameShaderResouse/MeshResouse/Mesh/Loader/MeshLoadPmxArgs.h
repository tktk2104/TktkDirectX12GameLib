#ifndef MESH_LOAD_PMX_ARGS_H_
#define MESH_LOAD_PMX_ARGS_H_

#include <string>

namespace tktk
{
	struct MeshLoadPmxArgs
	{
		// 作成する通常メッシュ情報のID
		int createBasicMeshId;

		// 作成するスケルトン情報のID
		int createSkeletonId;

		// 読み込むファイルパス
		std::string filePath;
	};
}
#endif // !MESH_LOAD_PMX_ARGS_H_