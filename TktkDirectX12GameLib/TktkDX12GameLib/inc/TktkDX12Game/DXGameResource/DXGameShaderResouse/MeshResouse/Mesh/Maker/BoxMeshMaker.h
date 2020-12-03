#ifndef BOX_MESH_MAKER_H_
#define BOX_MESH_MAKER_H_

#include <TktkMath/Structs/Color.h>

namespace tktk
{
	struct MeshDrawFuncRunnerInitParam;

	class BoxMeshMaker
	{
	public:

		BoxMeshMaker();
		~BoxMeshMaker();

	public:

		// �P�F�̗����̃��b�V�����C���[�t���[�������A���̃n���h����Ԃ�
		size_t makeBoxMeshWireFrame(const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// �P�F�̗����̃��b�V�������A���̃n���h����Ԃ�
		size_t makeMonoColorBoxMesh(const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

	public:

		// �e�N�X�`����\���������̃��b�V�������A���̃n���h����Ԃ�
		size_t makeBoxMesh(size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// �X�J�C�{�b�N�X���b�V�������A���̃n���h����Ԃ�
		size_t makeSkyBoxMesh(size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

	private:

		// �����̂̃C���f�b�N�X�T�C�Y
		constexpr static size_t IndicesSize{ 36U };
	};
}
#endif // !BOX_MESH_MAKER_H_