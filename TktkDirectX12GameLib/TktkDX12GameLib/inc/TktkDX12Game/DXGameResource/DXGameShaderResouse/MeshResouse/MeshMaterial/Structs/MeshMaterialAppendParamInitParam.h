#ifndef MESH_MATERIAL_APPEND_PARAM_INIT_PARAM_H_
#define MESH_MATERIAL_APPEND_PARAM_INIT_PARAM_H_

/* std::shared_ptr<> */
#include <memory>

namespace tktk
{
	// ���b�V���}�e���A���̒ǉ��p�����[�^�̏������ϐ�
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
