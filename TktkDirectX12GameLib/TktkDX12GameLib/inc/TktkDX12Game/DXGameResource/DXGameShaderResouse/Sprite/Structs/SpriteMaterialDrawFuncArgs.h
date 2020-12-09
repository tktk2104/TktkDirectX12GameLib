#ifndef SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_
#define SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_

/* class member */
#include <TktkMath/Structs/Color.h>

namespace tktk
{
	// �X�v���C�g�̃}�e���A����`�悷�鎞�ɕK�v�Ȉ���
	struct SpriteMaterialDrawFuncArgs
	{
		// �g�p����r���[�|�[�g�n���h��
		size_t			viewportHandle			;

		// �g�p����V�U�[��`�n���h��
		size_t			scissorRectHandle		;

		// �g�p���郌���_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�n���h��
		size_t			rtvDescriptorHeapHandle	;

		// �u�����h���[�g
		tktkMath::Color	blendRate				{ tktkMath::Color_v::white };
	};
}
#endif // !SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_