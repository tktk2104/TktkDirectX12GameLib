#ifndef RTV_DESCRIPTOR_HEAP_INIT_PARAM_H_
#define RTV_DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <vector>

namespace tktk
{
	// ���̃f�B�X�N���v�^�q�[�v�ň����o�b�t�@�[�̎��
	enum class RtvDescriptorType
	{
		normal,
		backBuffer
	};

	// �X�̃f�B�X�N���v�^�̏��
	struct RtvDescriptorParam
	{
		RtvDescriptorType	type;
		size_t				handle;
	};

	// �����_�[�^�[�Q�b�g�r���[�p�̃f�B�X�N���v�^�q�[�v����鎞�ɕK�v�ȕϐ�
	struct RtvDescriptorHeapInitParam
	{
		bool							shaderVisible{ true };
		std::vector<RtvDescriptorParam>	descriptorParamArray{ };
	};
}
#endif // !RTV_DESCRIPTOR_HEAP_INIT_PARAM_H_