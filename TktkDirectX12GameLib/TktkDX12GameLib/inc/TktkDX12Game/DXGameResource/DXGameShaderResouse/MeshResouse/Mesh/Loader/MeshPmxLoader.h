#ifndef MESH_PMX_LOADER_H_
#define MESH_PMX_LOADER_H_

#include "MeshLoadPmxArgs.h"
#include "MeshLoadPmxReturnValue.h"

namespace tktk
{
	// pmxファイルを読み込んで各種ゲームのリソースクラスを作るクラス
	class MeshPmxLoader
	{
	public:

		// pmxファイルを読み込んで各種ゲームのリソースクラスを作る
		static MeshLoadPmxReturnValue loadPmx(const MeshLoadPmxArgs& args);
	};
}
#endif // !BASIC_MESH_PMX_LOADER_H_