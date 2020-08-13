#ifndef SYSTEM_CBUFFER_TYPE_H_
#define SYSTEM_CBUFFER_TYPE_H_

namespace tktk
{
	// システムで使用している定数バッファの数
	constexpr unsigned int SystemCBufferNum = 8U;

	// システムで使用している定数バッファの種類
	enum class SystemCBufferType
	{
		Sprite				= 0U,
		Line2D,
		MeshTransform,
		MeshShadowMap,
		BoneMatCbuffer,
		Light,
		BasicMeshMaterial,
		BasicMonoColorMeshCbuffer
	};
}
#endif // !SYSTEM_CBUFFER_TYPE_H_