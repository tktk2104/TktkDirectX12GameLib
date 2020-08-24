#ifndef BUFFER_RESOURCE_INIT_PARAM_H_
#define BUFFER_RESOURCE_INIT_PARAM_H_

namespace tktk
{
	// ���ꂼ��̃o�b�t�@�[���\�[�X�̐���ݒ肷�邽�߂̍\����
	struct BufferResourceNum
	{
		unsigned int vertexBufferNum;		// ���_�o�b�t�@�̐�
		unsigned int indexBufferNum;		// �C���f�b�N�X�o�b�t�@�̐�
		unsigned int constantBufferNum;		// �萔�o�b�t�@�̐�
		unsigned int textureBufferNum;		// �e�N�X�`���o�b�t�@�̐�
		unsigned int depthStencilBufferNum;	// �[�x�X�e���V���o�b�t�@�̐�
		unsigned int renderTargetBufferNum;	// �����_�[�^�[�Q�b�g�o�b�t�@�̐�
	};
}
#endif // !BUFFER_RESOURCE_INIT_PARAM_H_