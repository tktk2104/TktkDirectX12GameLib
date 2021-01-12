#ifndef SPRITE_MATERIAL_INIT_PARAM_H_
#define SPRITE_MATERIAL_INIT_PARAM_H_

/* class member */
#include <TktkDX12Wrapper/Resource/Buffer/BufferType.h>

namespace tktk
{
	// �X�v���C�g�}�e���A�������Ƃ��ɕK�v�ȏ��
	struct SpriteMaterialInitParam
	{
		// �`�悷��o�b�t�@�[�̎��
		BufferType			srvBufferType;

		// �`�悷��o�b�t�@�[��ID
		size_t				useBufferHandle;

		// �`��ł���ő�C���X�^���X��
		size_t				maxInstanceCount;
	};
}
#endif // !SPRITE_MATERIAL_INIT_PARAM_H_