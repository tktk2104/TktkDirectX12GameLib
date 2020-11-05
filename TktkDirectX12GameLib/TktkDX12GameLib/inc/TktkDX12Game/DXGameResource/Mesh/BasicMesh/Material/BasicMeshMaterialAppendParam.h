#ifndef BASIC_MESH_MATERIAL_APPEND_PARAM_H_
#define BASIC_MESH_MATERIAL_APPEND_PARAM_H_

#include <memory>
#include <utility>

namespace tktk
{
	class BasicMeshMaterialAppendParam
	{
	public:

		BasicMeshMaterialAppendParam(size_t cbufferHandle, size_t dataSize, void* dataTopPos);
		~BasicMeshMaterialAppendParam();

		// ���[�u�R���X�g���N�^
		BasicMeshMaterialAppendParam(BasicMeshMaterialAppendParam&& other) noexcept;

	public:

		// �萔�o�b�t�@���X�V������e�̕ϐ�������������
		void updateParam(size_t dataSize, const void* dataTopPos);

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
#endif // !BASIC_MESH_MATERIAL_APPEND_PARAM_H_