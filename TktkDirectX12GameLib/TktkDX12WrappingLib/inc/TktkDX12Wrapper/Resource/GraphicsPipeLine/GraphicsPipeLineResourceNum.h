#ifndef GRAPHICS_PIPELINE_RESOURCE_NUM_H_
#define GRAPHICS_PIPELINE_RESOURCE_NUM_H_

#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>

namespace tktk
{
	struct GraphicsPipeLineResourceNum
	{
		tktkContainer::ResourceContainerInitParam pipeLineStateContainerInitParam;	// �p�C�v���C���X�e�[�g���Ǘ�����R���e�i�����������鎞�̒l
		tktkContainer::ResourceContainerInitParam rootSignatureContainerInitParam;	// ���[�g�V�O�l�`�����Ǘ�����R���e�i�����������鎞�̒l
	};
}
#endif // !GRAPHICS_PIPELINE_RESOURCE_NUM_H_