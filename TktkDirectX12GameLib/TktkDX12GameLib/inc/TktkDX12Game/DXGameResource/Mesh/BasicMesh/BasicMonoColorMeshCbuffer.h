#ifndef MONO_COLOR_CONSTANT_BUFFER_H_
#define MONO_COLOR_CONSTANT_BUFFER_H_

#include <TktkMath/Structs/Color.h>

namespace tktk
{
	// メッシュの単色塗りつぶし描画の定数バッファ
	struct BasicMonoColorMeshCbuffer
	{
		tktkMath::Color albedoColor;
	};
}
#endif // !MONO_COLOR_CONSTANT_BUFFER_H_
