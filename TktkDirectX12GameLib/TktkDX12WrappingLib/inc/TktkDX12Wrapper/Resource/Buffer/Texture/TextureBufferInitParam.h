#ifndef TEXTURE_BUFFER_INIT_PARAM_H_
#define TEXTURE_BUFFER_INIT_PARAM_H_

/* std::vector */
#include <vector>

/* D3D12_RESOURCE_DIMENSION, DXGI_FORMAT */
#include <d3d12.h>
#undef min
#undef max

namespace tktk
{
	// �e�N�X�`���f�[�^
	struct TexBuffData
	{
		std::vector<unsigned char>	textureData;	// ���̐F���f�[�^
		unsigned int				width;			// �e�N�X�`���̉���
		unsigned int				height;			// �e�N�X�`���̏c��
		unsigned int				depth;			// �e�N�X�`���̃{�����[��
	};

	// �e�N�X�`���̃t�H�[�}�b�g�f�[�^
	struct TexBufFormatParam
	{
		D3D12_RESOURCE_DIMENSION	resourceDimension;	// �������̃e�N�X�`�����H
		DXGI_FORMAT					format;				// �F���̃t�H�[�}�b�g
		unsigned int				arraySize;			// �e�N�X�`�����̔z��̐�
		unsigned int				mipLevels;			// �~�b�v���x��
		unsigned int				sampleDescCount;	// �T���v���f�X�N�̐�
		unsigned int				sampleDescQuality;	// �T���v���f�X�N�̕i��
	};
}
#endif // !TEXTURE_BUFFER_INIT_PARAM_H_