#ifndef MESH_PMX_LOADER_H_
#define MESH_PMX_LOADER_H_

#include "Structs/MeshLoadPmxArgs.h"
#include "Structs/MeshLoadPmxReturnValue.h"

namespace tktk
{
	struct MeshDrawFuncRunnerInitParam;

	// pmxファイルを読み込んで各種ゲームのリソースクラスを作るクラス
	class MeshPmxLoader
	{
	public:

		// pmxファイルを読み込んで各種ゲームのリソースクラスを作る
		static MeshLoadPmxReturnValue loadPmx(const MeshLoadPmxArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);
	};
}
#endif // !BASIC_MESH_PMX_LOADER_H_