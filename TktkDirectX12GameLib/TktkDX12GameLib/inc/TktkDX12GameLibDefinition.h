#ifndef TKTK_DX12_GAME_LIB_DEFINITION_H_
#define TKTK_DX12_GAME_LIB_DEFINITION_H_

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "xaudio2.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#if defined(NDEBUG) || !defined(_DEBUG)
#pragma comment( lib, "TktkDX12GameLib_mt.lib" )
#else
#pragma comment( lib, "TktkDX12GameLib_mtd.lib" )
#endif
#endif // !TKTK_DX12_GAME_LIB_DEFINITION_H_