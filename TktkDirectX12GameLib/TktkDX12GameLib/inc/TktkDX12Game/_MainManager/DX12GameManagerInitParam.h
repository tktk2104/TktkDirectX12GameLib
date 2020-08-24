#ifndef DX_12_GAME_MANAGER_INIT_PARAM_H_
#define DX_12_GAME_MANAGER_INIT_PARAM_H_

#include <string>
#include <TktkDX12Wrapper/Resource/DX3DResourceNum.h>
#include <TktkDX12Wrapper/Window/WindowInitParam.h>
#include "TktkDX12Game/DXGameResource/DXGameResourceNum.h"

namespace tktk
{
	struct DX12GameManagerInitParam
	{
		DX3DResourceNum				dx3dResNum		{};
		WindowInitParam				windowParam			{};
		DXGameResourceNum			dxGameResourceNum	{};
		std::string					tktkLibResFolderPath{""};
		bool						craeteDebugLayer	{ true };
	};
}
#endif // !DX_12_GAME_MANAGER_INIT_PARAM_H_