#ifndef SYSTEM_CBUFFER_TYPE_H_
#define SYSTEM_CBUFFER_TYPE_H_

namespace tktk
{
	// システムで使用している定数バッファの種類
	enum class SystemCBufferType
	{
		DrawGameArea,
		SpriteTransform,
		SpriteMaterialManager,
		Line2D,
		Billboard,
		Camera,
		ShadowMap,
		Light,
		MeshMaterial,
		MonoColorMesh
	};
}
#endif // !SYSTEM_CBUFFER_TYPE_H_