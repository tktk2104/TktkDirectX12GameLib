#ifndef MESH_LOAD_PMD_ARGS_H_
#define MESH_LOAD_PMD_ARGS_H_

#include <string>
#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

namespace tktk
{
	// pmdファイルを読み込むときに必要な情報
	struct MeshLoadPmdArgs
	{
		// 作成する通常メッシュ情報のID
		ResourceIdCarrier createBasicMeshId;

		// 作成するスケルトン情報のID
		ResourceIdCarrier createSkeletonId;

		// 読み込むファイルパス
		std::string filePath;
	};
}
#endif // !MESH_LOAD_PMD_ARGS_H_
