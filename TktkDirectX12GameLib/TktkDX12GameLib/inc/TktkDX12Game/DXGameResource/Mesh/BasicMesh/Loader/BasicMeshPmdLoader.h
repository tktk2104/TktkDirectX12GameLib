#ifndef BASIC_MESH_PMD_LOADER_H_
#define BASIC_MESH_PMD_LOADER_H_

#include "BasicMeshLoadPmdArgs.h"
#include "BasicMeshLoadPmdReturnValue.h"

namespace tktk
{
	// pmdファイルを読み込んで各種ゲームのリソースクラスを作るクラス
	class BasicMeshPmdLoader
	{
	public:

		// pmdファイルを読み込んで各種ゲームのリソースクラスを作る
		static BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);
	};
}
#endif // !BASIC_MESH_PMD_LOADER_H_
