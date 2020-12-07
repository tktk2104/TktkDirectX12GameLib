#ifndef MESH_PMD_LOADER_H_
#define MESH_PMD_LOADER_H_

#include "Structs/MeshLoadPmdArgs.h"
#include "Structs/MeshLoadPmdReturnValue.h"

namespace tktk
{
	struct MeshDrawFuncRunnerInitParam;

	// pmdファイルを読み込んで各種ゲームのリソースクラスを作るクラス
	class MeshPmdLoader
	{
	public:

		// pmdファイルを読み込んで各種ゲームのリソースクラスを作る
		static MeshLoadPmdReturnValue loadPmd(const MeshLoadPmdArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);
	};
}
#endif // !MESH_PMD_LOADER_H_