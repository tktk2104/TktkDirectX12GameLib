#ifndef POST_EFFECT_MATERIAL_APPEND_PARAM_INIT_PARAM_H_
#define POST_EFFECT_MATERIAL_APPEND_PARAM_INIT_PARAM_H_

/* std::shared_ptr<> */
#include <memory>

namespace tktk
{
	// ポストエフェクトマテリアルの追加パラメータの初期化変数
	struct PostEffectMaterialAppendParamInitParam
	{
	public:

		template <class CbufferType>
		PostEffectMaterialAppendParamInitParam(size_t cbufferHandle, const std::shared_ptr<CbufferType>& cbufferData)
			: cbufferHandle(cbufferHandle)
			, dataSize(sizeof(CbufferType))
			, cbufferDataPtr(cbufferData) {};

	public:

		size_t					cbufferHandle;
		size_t					dataSize;
		std::shared_ptr<void>	cbufferDataPtr;
	};
}
#endif // !POST_EFFECT_MATERIAL_APPEND_PARAM_INIT_PARAM_H_
