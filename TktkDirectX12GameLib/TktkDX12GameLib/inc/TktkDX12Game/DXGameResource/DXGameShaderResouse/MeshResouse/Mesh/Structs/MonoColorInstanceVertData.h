#ifndef MONO_COLOR_INSTANCE_VERT_DATA_H_
#define MONO_COLOR_INSTANCE_VERT_DATA_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// 単色メッシュのインスタンス描画用頂点バッファ形式
	struct MonoColorInstanceVertData
	{
		tktkMath::Matrix4	worldMatrix;
		tktkMath::Color		albedoColor;
	};
}
#endif // !MONO_COLOR_INSTANCE_VERT_DATA_H_