#ifndef DX_12_GAME_MANAGER_INIT_PARAM_H_
#define DX_12_GAME_MANAGER_INIT_PARAM_H_

#include <string>
#include <TktkDX12Wrapper/Resource/DX3DResourceNum.h>
#include "../GraphicManager/Window/WindowInitParam.h"

namespace tktk
{
	struct DX12GameManagerInitParam
	{
		// DirectX12のラッパークラスの初期化に必要な変数
		DX3DResourceNum				dx3dResNum			{};

		// ウィンドウの初期化に必要な変数
		WindowInitParam				windowParam			{};

		// このフレームワークの基本リソースのフォルダ階層
		std::string					tktkLibResFolderPath{""};

		// DirectX12のデバックレイヤーを作るかどうか？
		bool						craeteDebugLayer	{ true };

		// このフレームワークのリソース管理コンテナのメモリ確保関係の設定変数
		tktkContainer::ResourceContainerInitParam lightContainerParam;
		tktkContainer::ResourceContainerInitParam cameraContainerParam;
		tktkContainer::ResourceContainerInitParam postEffectMatContainerParam;
		tktkContainer::ResourceContainerInitParam line2DMatContainerParam;
		tktkContainer::ResourceContainerInitParam spriteMatContainerParam;
		tktkContainer::ResourceContainerInitParam billboardMatContainerParam;
		tktkContainer::ResourceContainerInitParam meshContainerParam;
		tktkContainer::ResourceContainerInitParam meshMatContainerParam;
		tktkContainer::ResourceContainerInitParam skeletonContainerParam;
		tktkContainer::ResourceContainerInitParam motionContainerParam;
		tktkContainer::ResourceContainerInitParam sceneContainerParam;
		tktkContainer::ResourceContainerInitParam soundContainerParam;
	};
}
#endif // !DX_12_GAME_MANAGER_INIT_PARAM_H_