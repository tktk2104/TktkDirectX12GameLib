#ifndef COPY_BUFFER_INIT_PARAM_H_
#define COPY_BUFFER_INIT_PARAM_H_

#include "../BufferType.h"

namespace tktk
{
	struct CopyBufferInitParam
	{
		// �R�s�[�Ώۂ̃o�b�t�@�[�̎��
		BufferType		targetBufferType;

		// �R�s�[�Ώۂ̃o�b�t�@�[�̃n���h��
		unsigned int	targetBufferHandle;

		// �o�b�t�@�[�̑傫��
		unsigned int	bufferWidth;

		// �o�b�t�@�[�̐擪�|�C���^
		const void*		dataTopPos;
	};
}
#endif // !COPY_BUFFER_INIT_PARAM_H_