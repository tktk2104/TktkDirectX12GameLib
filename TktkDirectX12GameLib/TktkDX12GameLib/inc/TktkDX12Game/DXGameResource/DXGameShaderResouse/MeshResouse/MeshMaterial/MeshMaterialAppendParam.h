#ifndef MESH_MATERIAL_APPEND_PARAM_H_
#define MESH_MATERIAL_APPEND_PARAM_H_

/* std::shared_ptr<> */
#include <memory>

namespace tktk
{
	struct MeshMaterialAppendParamInitParam;
	struct MeshMaterialAppendParamUpdateFuncArgs;

	// ���b�V���}�e���A���̒ǉ��p�����[�^
	class MeshMaterialAppendParam
	{
	public:

		MeshMaterialAppendParam(const MeshMaterialAppendParamInitParam& initParam);
		~MeshMaterialAppendParam();

		// ���[�u�R���X�g���N�^
		MeshMaterialAppendParam(MeshMaterialAppendParam&& other) noexcept;

	public:

		// �萔�o�b�t�@���X�V������e�̕ϐ�������������
		void updateParam(const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

		// �萔�o�b�t�@���X�V����
		void updateCbuffer() const;

	private:

		// �萔�o�b�t�@�̃R�s�[�p�o�b�t�@���X�V����
		void updateCopyBuffer() const;

	private:

		// �萔�o�b�t�@�ɃR�s�[����ׂ̃o�b�t�@�n���h��
		size_t	m_createUploadBufferHandle{ 0U };

		// �ύX�Ώۂ̒萔�o�b�t�@�n���h��
		size_t	m_cbufferHandle;

		// �萔�o�b�t�@�̑傫��
		size_t	m_dataSize;

		// �萔�o�b�t�@���X�V������e�̕ϐ��̃|�C���^
		std::shared_ptr<void> m_dataTopPos;
	};
}
#endif // !MESH_MATERIAL_APPEND_PARAM_H_