#ifndef BASIC_DESCRIPTOR_HEAP_INIT_PARAM_H_
#define BASIC_DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <vector>
#include "../../Buffer/BufferType.h"

namespace tktk
{
	// �X�̃f�B�X�N���v�^�̏��
	struct BasicDescriptorParam
	{
		BufferType			type	{};
		size_t				handle	{};
	};

	// ���̃f�B�X�N���v�^�q�[�v�ň����o�b�t�@�[�̎��
	enum class BasicDescriptorType
	{
		constantBuffer,
		textureBuffer,
	};

	// �f�B�X�N���v�^�e�[�u������鎞�ɕK�v�ȕϐ�
	struct BasicDescriptorTableParam
	{
		BasicDescriptorType					type				{};
		std::vector<BasicDescriptorParam>	descriptorParamArray{};
	};

	// �uCBV_SRV_UAV�v�̃f�B�X�N���v�^�q�[�v����邽�߂̃f�[�^
	struct BasicDescriptorHeapInitParam
	{
		bool									shaderVisible				{ true };
		std::vector<BasicDescriptorTableParam>	descriptorTableParamArray	{ };
	};
}
#endif // !BASIC_DESCRIPTOR_HEAP_INIT_PARAM_H_