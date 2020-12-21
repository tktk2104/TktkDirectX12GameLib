#ifndef SYSTEM_TEXTURE_BUFFER_TYPE_H_
#define SYSTEM_TEXTURE_BUFFER_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���e�N�X�`���o�b�t�@�̎��
	enum class SystemTextureBufferType
	{
		White4x4,		// 4x4���e�N�X�`��
		Black4x4,		// 4x4���e�N�X�`��

		FlatNormal4x4,	// 4x4����Ȗ@���e�N�X�`��

		Text,			// �e�L�X�g�`��p�e�N�X�`��

		MeshBoneMatrix,	// �V�F�[�_�[�Ƀ{�[������n�����Ɏg�p����1D�e�N�X�`��
	};
}
#endif // !SYSTEM_TEXTURE_BUFFER_TYPE_H_