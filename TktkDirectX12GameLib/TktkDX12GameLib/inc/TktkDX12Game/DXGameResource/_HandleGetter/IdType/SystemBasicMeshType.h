#ifndef SYSTEM_BASIC_MESH_TYPE_H_
#define SYSTEM_BASIC_MESH_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���ʏ�̃��b�V���̐�
	constexpr unsigned int SystemBasicMeshNum = 2U;

	// �V�X�e���Ŏg�p���Ă���ʏ�̃��b�V���̎��
	enum class SystemBasicMeshType
	{
		Sphere = 0U,
		SphereWireFrame
	};
}
#endif // !SYSTEM_BASIC_MESH_TYPE_H_