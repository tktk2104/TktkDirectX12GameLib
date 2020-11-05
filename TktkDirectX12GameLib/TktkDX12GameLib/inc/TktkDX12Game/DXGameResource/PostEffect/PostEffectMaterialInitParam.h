#ifndef POST_EFFECT_MATERIAL_INIT_PARAM_H_
#define POST_EFFECT_MATERIAL_INIT_PARAM_H_

#include <vector>

namespace tktk
{
	// �|�X�g�G�t�F�N�g�̃}�e���A������鎞�ɕK�v�ȏ��
	struct PostEffectMaterialInitParam
	{
		// �g�p����p�C�v���C���X�e�[�g�n���h��
		size_t usePipeLineStateHandle;

		// �g�p����f�B�X�N���v�^�q�[�v�n���h��
		size_t useDescriptorHeapHandle;

		// �`��㎩���ŃN���A���郌���_�[�^�[�Q�b�g�r���[�p�̃f�B�X�N���v�^�q�[�v�n���h���̔z��
		std::vector<size_t> autoClearRtvDescriptorHeapHandleArray;
	};
}
#endif // !POST_EFFECT_MATERIAL_INIT_PARAM_H_