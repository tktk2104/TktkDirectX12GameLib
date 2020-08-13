#ifndef BUFFER_TYPE_H_
#define BUFFER_TYPE_H_

namespace tktk
{
	// �o�b�t�@�[�̎��
	enum class BufferType
	{
		vertex,			// ���_�o�b�t�@
		index,			// �C���f�b�N�X�o�b�t�@
		constant,		// �萔�o�b�t�@
		texture,		// �e�N�X�`���o�b�t�@
		renderTarget,	// �[�x�X�e���V���o�b�t�@
		depthStencil	// �����_�[�^�[�Q�b�g�o�b�t�@
	};
}
#endif // !BUFFER_TYPE_H_