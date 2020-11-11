#ifndef MESH_MATERIAL_APPEND_PARAM_INIT_PARAM_H_
#define MESH_MATERIAL_APPEND_PARAM_INIT_PARAM_H_

/* std::shared_ptr<> */
#include <memory>

namespace tktk
{
	// ���b�V���}�e���A���̒ǉ��p�����[�^�̏������ϐ�
	struct MeshMaterialAppendParamInitParam
	{
		size_t					cbufferHandle;
		size_t					dataSize;
		std::shared_ptr<void>	dataTopPos;
	};
}
#endif // !MESH_MATERIAL_APPEND_PARAM_INIT_PARAM_H_
