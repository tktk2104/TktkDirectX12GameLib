#ifndef BASIC_MESH_LOAD_PMD_ARGS_H_
#define BASIC_MESH_LOAD_PMD_ARGS_H_

#include <string>

namespace tktk
{
	// pmdファイルを読み込むときに必要な情報
	struct BasicMeshLoadPmdArgs
	{
		// 作成する通常メッシュ情報のID
		unsigned int createBasicMeshId;

		// 作成するスケルトン情報のID
		unsigned int createSkeletonId;

		// 読み込むファイルパス
		std::string filePath;
	};
}
#endif // !BASIC_MESH_LOAD_PMD_ARGS_H_
