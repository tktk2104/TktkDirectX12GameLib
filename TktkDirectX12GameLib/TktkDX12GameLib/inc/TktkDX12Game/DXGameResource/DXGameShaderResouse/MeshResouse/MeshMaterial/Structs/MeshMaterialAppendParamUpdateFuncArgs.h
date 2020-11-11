#ifndef MESH_MATERIAL_APPEND_PARAM_UPDATE_FUNC_ARGS_H_
#define MESH_MATERIAL_APPEND_PARAM_UPDATE_FUNC_ARGS_H_

namespace tktk
{
	struct MeshMaterialAppendParamUpdateFuncArgs
	{
	public:

		template <class CbufferType>
		MeshMaterialAppendParamUpdateFuncArgs(size_t cbufferHandle, const CbufferType& cbufferData)
			: cbufferHandle(cbufferHandle)
			, dataSize(sizeof(CbufferType))
			, dataTopPos(&cbufferData) {};

	public:

		size_t		cbufferHandle;
		size_t		dataSize;
		const void* dataTopPos;
	};
}
#endif // !MESH_MATERIAL_APPEND_PARAM_UPDATE_FUNC_ARGS_H_
