#ifndef DESCRIPTOR_HEAP_INIT_PARAM_H_
#define DESCRIPTOR_HEAP_INIT_PARAM_H_

#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>

namespace tktk
{
	struct DescriptorHeapNum
	{
		tktkContainer::ResourceContainerInitParam basicDescriptorHeapContainerInitParam;	// �ʏ�̃f�B�X�N���v�^�q�[�v���Ǘ�����R���e�i�����������鎞�̒l
		tktkContainer::ResourceContainerInitParam rtvDescriptorHeapContainerInitParam;		// �����_�[�^�[�Q�b�g�r���[�p�̃f�B�X�N���v�^�q�[�v���Ǘ�����R���e�i�����������鎞�̒l
		tktkContainer::ResourceContainerInitParam dsvDescriptorHeapContainerInitParam;		// �[�x�X�e���V���r���[�p�̃f�B�X�N���v�^�q�[�v���Ǘ�����R���e�i�����������鎞�̒l
	};
}
#endif // !DESCRIPTOR_HEAP_INIT_PARAM_H_