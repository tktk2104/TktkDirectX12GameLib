#ifndef SYSTEM_RTV_DESCRIPTOR_HEAP_TYPE_H_
#define SYSTEM_RTV_DESCRIPTOR_HEAP_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă��郌���_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�̎��
	enum class SystemRtvDescriptorHeapType
	{
		BackBuffer,			// �o�b�N�o�b�t�@�[
		DrawGameArea,		// �Q�[���̕`��G���A
		PostEffectTarget,	// �|�X�g�G�t�F�N�g�o��
	};
}
#endif // !SYSTEM_RTV_DESCRIPTOR_HEAP_TYPE_H_