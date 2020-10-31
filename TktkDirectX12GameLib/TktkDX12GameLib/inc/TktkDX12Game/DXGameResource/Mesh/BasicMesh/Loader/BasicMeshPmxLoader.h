#ifndef BASIC_MESH_PMX_LOADER_H_
#define BASIC_MESH_PMX_LOADER_H_

#include "BasicMeshLoadPmxArgs.h"
#include "BasicMeshLoadPmxReturnValue.h"

namespace tktk
{
	// pmxファイルを読み込んで各種ゲームのリソースクラスを作るクラス
	class BasicMeshPmxLoader
	{
	public:

		// pmxファイルを読み込んで各種ゲームのリソースクラスを作る
		static BasicMeshLoadPmxReturnValue loadPmx(const BasicMeshLoadPmxArgs& args);
	};
}
#endif // !BASIC_MESH_PMX_LOADER_H_