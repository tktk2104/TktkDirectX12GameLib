#ifndef POST_EFFECT_MATERIAL_APPEND_PARAM_UPDATE_FUNC_ARGS_H_
#define POST_EFFECT_MATERIAL_APPEND_PARAM_UPDATE_FUNC_ARGS_H_

namespace tktk
{
	struct PostEffectMaterialAppendParamUpdateFuncArgs
	{
	public:

		template <class CbufferType>
		PostEffectMaterialAppendParamUpdateFuncArgs(size_t cbufferHandle, const CbufferType& cbufferData)
			: cbufferHandle(cbufferHandle)
			, dataSize(sizeof(CbufferType))
			, dataTopPos(&cbufferData) {};

	public:

		size_t		cbufferHandle;
		size_t		dataSize;
		const void* dataTopPos;
	};
}
#endif // !POST_EFFECT_MATERIAL_APPEND_PARAM_UPDATE_FUNC_ARGS_H_