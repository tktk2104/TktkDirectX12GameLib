#ifndef SPHERE_MESH_MAKER_H_
#define SPHERE_MESH_MAKER_H_

#include <TktkMath/Structs/Color.h>

namespace tktk
{
	struct MeshDrawFuncRunnerInitParam;

	class SphereMeshMaker
	{
	public:

		SphereMeshMaker();
		~SphereMeshMaker();

	public:

		// ���̃��C���[�t���[�����b�V�������
		size_t makeSphereMeshWireFrame(const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// ���̒P�F���b�V�������
		size_t makeMonoColorSphereMesh(const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

	private:

		// ���̂̃C���f�b�N�X�T�C�Y
		constexpr static size_t IndicesSize{ 600U };
	};
}
#endif // !SPHERE_MESH_MAKER_H_