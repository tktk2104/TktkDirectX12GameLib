#ifndef LIGHT_CBUFFER_H_
#define LIGHT_CBUFFER_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	// ライト情報の定数バッファ
	struct LightCBuffer
	{
		// ライトの環境光
		tktkMath::Color		lightAmbient	{ 0.25f, 1.0f };

		// ライトの拡散反射光
		tktkMath::Color		lightDiffuse	{ 0.25f, 1.0f };

		// ライトの鏡面反射光
		tktkMath::Color		lightSpeqular	{ 0.25f, 1.0f };

		// ライトの座標
		tktkMath::Vector3	lightPosition	{ tktkMath::Vector3_v::zero };

		// パディング
		float				lightDataPad	{ 0.0f };
	};
}
#endif // !LIGHT_CBUFFER_H_
