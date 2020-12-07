#ifndef POST_EFFECT_MATERIAL_APPEND_PARAM_H_
#define POST_EFFECT_MATERIAL_APPEND_PARAM_H_

/* std::shared_ptr<> */
#include <memory>

namespace tktk
{
	struct PostEffectMaterialAppendParamInitParam;
	struct PostEffectMaterialAppendParamUpdateFuncArgs;

	// �|�X�g�G�t�F�N�g�}�e���A���̒ǉ��p�����[�^
	class PostEffectMaterialAppendParam
	{
	public:

		PostEffectMaterialAppendParam(const PostEffectMaterialAppendParamInitParam& initParam);
		~PostEffectMaterialAppendParam();

		// ���[�u�R���X�g���N�^
		PostEffectMaterialAppendParam(PostEffectMaterialAppendParam&& other) noexcept;

	public:

		// �萔�o�b�t�@���X�V������e�̕ϐ�������������
		void updateParam(const PostEffectMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

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
#endif // !POST_EFFECT_MATERIAL_APPEND_PARAM_H_