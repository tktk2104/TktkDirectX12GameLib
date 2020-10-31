#ifndef BASIC_MESH_LOAD_PMX_ARGS_H_
#define BASIC_MESH_LOAD_PMX_ARGS_H_

#include <string>

namespace tktk
{
	struct BasicMeshLoadPmxArgs
	{
		// 作成する通常メッシュ情報のID
		int createBasicMeshId;

		// 作成するスケルトン情報のID
		int createSkeletonId;

		// 読み込むファイルパス
		std::string filePath;
	};
}
#endif // !BASIC_MESH_LOAD_PMX_ARGS_H_