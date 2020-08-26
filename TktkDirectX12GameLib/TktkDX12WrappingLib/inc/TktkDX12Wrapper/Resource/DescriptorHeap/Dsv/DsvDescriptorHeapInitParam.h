#ifndef DSV_DESCRIPTOR_HEAP_INIT_PARAM_H_
#define DSV_DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <vector>

namespace tktk
{
	// ���̃f�B�X�N���v�^�q�[�v�ň����o�b�t�@�[�̎��
	enum class DsvDescriptorType
	{
		normal,
	};

	// �X�̃f�B�X�N���v�^�̏��
	struct DsvDescriptorParam
	{
		DsvDescriptorType	type;
		unsigned int		handle;
	};

	// �[�x�X�e���V���r���[�p�̃f�B�X�N���v�^�q�[�v����鎞�ɕK�v�ȕϐ�
	struct DsvDescriptorHeapInitParam
	{
		bool							shaderVisible{ true };
		std::vector<DsvDescriptorParam>	descriptorParamArray{ };
	};
}
#endif // !DSV_DESCRIPTOR_HEAP_INIT_PARAM_H_