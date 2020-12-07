#ifndef MONO_COLOR_CBUFFER_DATA_H_
#define MONO_COLOR_CBUFFER_DATA_H_

/* class member */
#include <TktkMath/Structs/Color.h>

namespace tktk
{
	// メッシュの単色塗りつぶし描画の定数バッファ
	struct MonoColorMeshCBufferData
	{
		tktkMath::Color albedoColor;
	};
}
#endif // !MONO_COLOR_CBUFFER_DATA_H_
