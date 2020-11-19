#ifndef MESH_MATERIAL_APPEND_PARAM_INIT_PARAM_H_
#define MESH_MATERIAL_APPEND_PARAM_INIT_PARAM_H_

/* std::shared_ptr<> */
#include <memory>

namespace tktk
{
	// メッシュマテリアルの追加パラメータの初期化変数
	struct MeshMaterialAppendParamInitParam
	{
	public:

		template <class CbufferType>
		MeshMaterialAppendParamInitParam(size_t cbufferHandle, const std::shared_ptr<CbufferType>& cbufferData)
			: cbufferHandle(cbufferHandle)
			, dataSize(sizeof(CbufferType))
			, cbufferDataPtr(cbufferData) {};

	public:

		size_t					cbufferHandle;
		size_t					dataSize;
		std::shared_ptr<void>	cbufferDataPtr;
	};
}
#endif // !MESH_MATERIAL_APPEND_PARAM_INIT_PARAM_H_
